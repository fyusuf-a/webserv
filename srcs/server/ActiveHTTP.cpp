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
		//_ongoing_tasks.pop_front();
	}
	if (_chain)
		delete _chain;
}

bool	ActiveHTTP::on_readable(int fd) {
	postpone_timeout();
	if (!ActiveServer::on_readable(fd)) {
		return (false);
	}
	std::ostringstream	ss;

	_request.set_over(true);
	if (_request.get_head() != 6) {
		while (_request.get_head() < 6 && _request.get_over())
			_request.parse(_read_buffer);
	}
	// If the request is parsed and the middleware chain is not launched, launch
	// it
	if (_request.get_head() == 6) {
		launch_middleware_chain();
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
		postpone_timeout();

	// If the request timed out, delete the ActiveHTTP server
	if (!check_timeout(fd))
		return (false);
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

//Todo: verify that no task stays running
void	ActiveHTTP::reinitialize() {
	_request.reinitialize();
	_response.reinitialize();
	_delegation_to_task = false;
	LOG.debug() << "ActiveHTTP server is reinitialized" << std::endl;
}
