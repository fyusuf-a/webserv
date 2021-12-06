#include "ActiveHTTP.hpp"
#include "ActiveServer.hpp"
#include "NIOSelector.hpp"
#include "../utils/Log.hpp"
#include <ctime>
#include <ostream>
#include <sstream>
#include "../http/Response/Response.hpp"
#include "../http/tasks/Task.hpp"

Log& ActiveHTTP::LOG = Log::getInstance();

ActiveHTTP::ActiveHTTP() : ActiveServer(), _server_blocks(NULL), _chain(NULL),
							_ongoing_task(NULL)
{
	time(&_last_time_active);
}

ActiveHTTP::ActiveHTTP(const ActiveHTTP& src) : ActiveServer(src),
	_server_blocks(src._server_blocks), _chain(NULL), _ongoing_task(NULL)
{
	*this = src;
}

ActiveHTTP::ActiveHTTP(Socket* socket, INetAddress const& interface, std::vector<ServerBlock> const* server_blocks)
													: ActiveServer(socket)
													, _interface(interface)
													, _server_blocks(server_blocks)
													, _chain(NULL)
													, _ongoing_task(NULL)
{
	time(&_last_time_active);
}

ActiveHTTP::ActiveHTTP(Socket* socket)
													: ActiveServer(socket)
													, _server_blocks(NULL)
													, _chain(NULL)
													, _ongoing_task(NULL)
{
	time(&_last_time_active);
}

ActiveHTTP& ActiveHTTP::operator=(const ActiveHTTP& src) {
	if (this != &src) {
		ActiveServer::operator=(src);
		_last_time_active = src._last_time_active;
		_interface = src._interface;
		_server_blocks = src._server_blocks;
		_request = src._request;
		_response = src._response;
		_chain = src._chain;
		_task_ongoing = src._task_ongoing;
		_ongoing_task = src._ongoing_task;
	}
	return (*this);
}

ActiveHTTP::~ActiveHTTP() {
	if (_ongoing_task)
		delete _ongoing_task;
	if (_chain)
		delete _chain;
}

bool	ActiveHTTP::on_readable(int fd) {
	postpone_timeout();
	if (!ActiveServer::on_readable(fd)) {
		return (false);
	}
	std::ostringstream	ss;

	//std::cout << "readbuffer avant parsing:" << std::endl
	//			  << "(" << _read_buffer << ")" << std::endl;
	_request.set_over(true);
	if (_request.get_head() != 6) {
		while (_request.get_head() < 6 && _request.get_over())
			_request.parse(_read_buffer);
	}

	//LOG.debug() << "----------------- parsed request" << std::endl;

	//std::cout << "readbuffer after parsing: " << std::endl
	//	  << "(" << _read_buffer << ")" << std::endl;
	//LOG.debug() << "end of parsing" << std::endl;
	return (true);
}

bool	ActiveHTTP::on_writable(int fd) {
	postpone_timeout();
	return ActiveServer::on_writable(fd);
}

bool	ActiveHTTP::always(int fd) {
	(void)fd;

	// If a request is parsed and a task is still running, the server should not timeout
	if (_response.get_ready() && !_response.get_written_on_write_buffer())
		postpone_timeout();

	// If the request is parsed and the middleware chain is not launched, launch
	// it
	if (!_request.get_treated_by_middlewares() && _request.get_head() == 6) {
		LOG.debug() << "Launch middleware chain" << std::endl;
		launch_middleware_chain();
	}

	// If the response has been wholly treated by the middleware chain, write it
	// on the write buffer (if the end of the response is delegated to a task,
	// only write the beginning of the response)
	if (_response.get_ready() && _ongoing_task && !_response.get_beginning_written_on_write_buffer())
		write_beginning_on_write_buffer();
		
	if (_response.get_ready() && !_ongoing_task && !_response.get_written_on_write_buffer())
		write_all_on_write_buffer();

	if (_response.get_written_on_write_buffer() && !_ongoing_task) {
		_request.reinitialize();
		_response.reinitialize();
		LOG.debug() << "ActiveHTTP server is reinitialized" << std::endl;
	}

	// If the request timed out, delete the ActiveHTTP server
	if (!check_timeout(fd))
		return (false);
	return (true);
}

bool	ActiveHTTP::on_close(int fd) {
	NIOSelector::getInstance().remove(fd);
	delete (this);
	return (false);
}

std::vector<ServerBlock> const* ActiveHTTP::getServerBlocks() const {
	return _server_blocks;
}

INetAddress ActiveHTTP::getInterface() const {
	return _interface;
}

Task const* ActiveHTTP::get_ongoing_task() const {
	return _ongoing_task;
}

void ActiveHTTP::setServerBlocks(std::vector<ServerBlock> const* server_blocks) {
	_server_blocks = server_blocks;
}

void ActiveHTTP::set_ongoing_task(Task* task) {
	_ongoing_task = task;
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

void	ActiveHTTP::postpone_timeout() {
	time(&_last_time_active);
}

bool	ActiveHTTP::check_timeout(int fd) {
	time_t				now;

	time(&now);
	if (difftime(now, _last_time_active) > TIMEOUT)
	{
		LOG.info() << "Connection timed out" << std::endl;
		on_close(fd);
		return (false);
	}
	return (true);
}

void	ActiveHTTP::launch_middleware_chain() {	
	if (_chain)
	{
		delete _chain;
		_chain = NULL;
	}
	_chain = new MiddlewareChain(this, &_request, &_response);
	LOG.debug() << "Beginning of the treatment of the request by the middlewares" << std::endl;
	_request.set_treated_by_middlewares(true);
	(*_chain)();
}

void	ActiveHTTP::write_beginning_on_write_buffer() {	
	std::ostringstream os;
	os < _response;
	_write_buffer += os.str();
	LOG.debug() << "Beginning of the request written on the write buffer" << std::endl;
	_response.set_beginning_written_on_write_buffer(true);
}

void	ActiveHTTP::write_all_on_write_buffer() {	
	std::ostringstream os;
	os << _response;
	_write_buffer += os.str();
	LOG.debug() << "Request totally written on the write buffer" << std::endl;
	_response.set_written_on_write_buffer(true);
}

/*void	ActiveHTTP::send_partial_response(const std::string& str) {	
	std::ostringstream oss;
	_write_buffer += str;
}*/
