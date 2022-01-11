#include "ActiveHTTP.hpp"
#include "ActiveServer.hpp"
#include "NIOSelector.hpp"
#include "../utils/Log.hpp"
#include <ctime>
#include <ostream>
#include <sstream>
#include "../http/Response/Response.hpp"
#include "../http/tasks/Task.hpp"

void		block_selector(ActiveHTTP& actHTTP, Request& request, Response& response);

Log& ActiveHTTP::LOG = Log::getInstance();

ActiveHTTP::ActiveHTTP() : ActiveServer(), _server_blocks(NULL), _chain(NULL),
	_delegation_to_task(false)
{
	time(&_last_time_active);
}

ActiveHTTP::ActiveHTTP(Socket* socket, INetAddress const& interface, std::vector<ServerBlock> const* server_blocks)
													: ActiveServer(socket)
													, _interface(interface)
													, _server_blocks(server_blocks)
													, _chain(NULL)
													, _delegation_to_task(false)
{
	_original_port = interface.getPort();
	time(&_last_time_active);
}

ActiveHTTP::ActiveHTTP(Socket* socket) : ActiveServer(socket)
										, _server_blocks(NULL)
										, _chain(NULL)
										, _delegation_to_task(false)
									
{
	time(&_last_time_active);
}

ActiveHTTP::~ActiveHTTP() {
	while (!_ongoing_tasks.empty())
	{
		Task* task = _ongoing_tasks.front();
		task->on_close(task->get_fd());
	}
	if (_chain)
		delete _chain;
}

void ActiveHTTP::add_content_length(std::ostringstream& oss) {
	Response::header_map const& headers = _response.get_headers();
	Response::header_map::const_iterator it = headers.find("Content-Length");
	if (it == headers.end())
	{
		oss << _response.get_body().length();
		_response.set_header("Content-Length", oss.str()); 
		oss.str("");
	}
}


bool	ActiveHTTP::on_readable(int fd) {
#ifdef DEBUG_FLAG
	static size_t request_number = 1;
#endif
	postpone_timeout();
	if (!ActiveServer::on_readable(fd)) {
		return (false);
	}
	_request.set_over(true);

	bool location_set = false;

	if (_request.get_head() != 6) {
		while (_request.get_head() < 6 && _request.get_over()) {
			if (_request.get_head() == 5 && !location_set) {
				location_set = true;
				block_selector(*this, _request, _response);
				if (_request.get_location().get_body_size() == std::string::npos)
					_request.get_location().set_body_size(100000000);
			}
			_request.parse(_read_buffer);
		}
#ifdef DEBUG_FLAG
		if (_request.get_head() == 6) {
			LOG.debug() << "REQUEST NO " << request_number << std::endl;
			request_number++;
			LOG.debug() < _request;
			if (!_request.get_body().empty())
				LOG.debug() << "[BODY OF " << _request.get_body().size() << " ]";
			else
				LOG.debug() << "[EMPTY BODY]";
			LOG.debug() << std::endl;
		}
#endif
	}

	if (!location_set && _request.get_head() == 6)
		block_selector(*this, _request, _response);
	// If the request is parsed and the middleware chain is not launched, launch
	// it
	if (_request.get_head() == 6) {
		launch_middleware_chain(fd);
		// If there is no ongoing task, set the response length to the length of
		// the body produced by the middlewares, and send the response
		if (!_delegation_to_task)
		{
			std::ostringstream oss;
			add_content_length(oss);
			oss << _response;
			_write_buffer += oss.str();
			LOG.debug() << "Request totally written on the write buffer (fd = "<< fd << ")" << std::endl;
			if (reinitialize(fd) == false)
				return false;
		}
	}
	return (true);
}

bool	ActiveHTTP::on_writable(int fd) {
	postpone_timeout();
	return ActiveServer::on_writable(fd);
}

bool	ActiveHTTP::always(int fd) {
	// If a request is parsed and a task is still running, the server should not timeout
	if (_response.get_ready())
	{
		//LOG.debug() << "postponing timeout for fd " << fd << std::endl;
		postpone_timeout();
	}

	// If the request timed out, delete the ActiveHTTP server
	if (!check_timeout(fd))
	{
		LOG.debug() << "A timeout occured because on fd " << fd << std::endl;
		return (false);
	}
	return (true);
}

bool ActiveHTTP::on_close(int) {
	delete (this);
	return (false);
}

uint16_t ActiveHTTP::get_original_port() const {
	return _original_port;
}

std::vector<ServerBlock> const* ActiveHTTP::get_server_blocks() const {
	return _server_blocks;
}

INetAddress ActiveHTTP::get_interface() const {
	return _interface;
}

std::list<Task*> const& ActiveHTTP::get_ongoing_tasks() const {
	return _ongoing_tasks;
}

/*void ActiveHTTP::set_server_blocks(std::vector<ServerBlock> const* server_blocks) {
	_server_blocks = server_blocks;
}*/

void ActiveHTTP::set_delegation_to_task(bool set) {
	_delegation_to_task = set;
}

void ActiveHTTP::set_chain(MiddlewareChain* const& chain) {
	_chain = chain;
}

/*void ActiveHTTP::set_ongoing_tasks(std::list<Task*> const& tasks) {
	_ongoing_tasks = tasks;
}*/

void ActiveHTTP::add_ongoing_task(Task* const& task) {
	_ongoing_tasks.push_back(task);
}

void ActiveHTTP::remove_ongoing_task(Task* const& task) {
	_ongoing_tasks.remove(task);
}

time_t const& ActiveHTTP::get_last_time_active() const {
	return _last_time_active;
}

Request &ActiveHTTP::get_request() {
	return (_request);
}

Response &ActiveHTTP::get_response() {
	return (_response);
}

std::string& ActiveHTTP::get_write_buffer() {
	return (_write_buffer);
}

char* ActiveHTTP::get_tmp() {
	return (_tmp);
}

bool ActiveHTTP::get_delegation_to_task() const {
	return (_delegation_to_task);
}

void	ActiveHTTP::postpone_timeout() {
	time(&_last_time_active);
}

bool	ActiveHTTP::check_timeout(int fd) {
	time_t				now;

	time(&now);
	if (difftime(now, _last_time_active) > TIMEOUT)
	{
		LOG.info() << "Connection timed out (fd = "<< fd << ")" << std::endl;
		on_close(fd);
		return (false);
	}
	return (true);
}

void	ActiveHTTP::launch_middleware_chain(int fd) {	
	if (_chain)
	{
		delete _chain;
		_chain = NULL;
	}
	_chain = new MiddlewareChain(this, &_request, &_response);
	LOG.debug() << "Beginning of the treatment of the request by the middlewares (fd = "<< fd << ")" << std::endl;
	_request.set_treated_by_middlewares(true);
	(*_chain)();
}

void	ActiveHTTP::write_beginning_on_write_buffer(int fd) {	
	std::ostringstream os;
	os < _response;
	_write_buffer += os.str();
	LOG.debug() << "Beginning of the request written on the write buffer (fd = "<< fd << ")" << std::endl;
	_response.set_beginning_written_on_write_buffer(true);
}

bool	ActiveHTTP::reinitialize(int fd) {
	if (_request.get_wrong())
	{
		LOG.error() << "Request was malformed" << std::endl;
		on_close(_socket->getFd());
		return false;
	}
	_request = Request();
	_response = Response();
	_delegation_to_task = false;
	LOG.debug() << "ActiveHTTP server is reinitialized (fd = "<< fd << ")" << std::endl;
	return true;
}
