#include "ActiveHTTP.hpp"
#include "ActiveServer.hpp"
#include "NIOSelector.hpp"
#include "../utils/Log.hpp"
#include <ctime>
#include <ostream>
#include <sstream>
#include "../http/Response/Response.hpp"

Log& ActiveHTTP::LOG = Log::getInstance();

ActiveHTTP::ActiveHTTP() : ActiveServer(), _server_blocks(NULL), _chain(NULL) {
	time(&_last_time_active);
}

ActiveHTTP::ActiveHTTP(const ActiveHTTP& src) : ActiveServer(src), _server_blocks(src._server_blocks), _chain(NULL) {
	*this = src;
}

ActiveHTTP::ActiveHTTP(Socket* socket, INetAddress const& interface, std::vector<ServerBlock> const* server_blocks)
													: ActiveServer(socket)
													, _interface(interface)
													, _server_blocks(server_blocks)
													, _chain(NULL)
{
	time(&_last_time_active);
}

ActiveHTTP::ActiveHTTP(Socket* socket)
													: ActiveServer(socket)
													, _server_blocks(NULL)
													, _chain(NULL)
{
	time(&_last_time_active);
}

ActiveHTTP& ActiveHTTP::operator=(const ActiveHTTP& src) {
	if (this != &src) {
		ActiveServer::operator=(src);
		_last_time_active = src._last_time_active;
		_interface = src._interface;
		_server_blocks = src._server_blocks;
	}
	return (*this);
}

ActiveHTTP::~ActiveHTTP() {
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
				  //<< "(" << _read_buffer << ")" << std::endl;
				  
	if (_request.get_head() != 6) {
		while (_request.get_head() < 6 && _request.get_over())
			_request.parse(_read_buffer);
	}

	//LOG.debug() << "----------------- parsed request" << std::endl;
	//std::cout << _parsed_request << std::endl;

	//std::cout << "readbuffer after parsing: " << std::endl
			  //<< "(" << _read_buffer << ")" << std::endl;
	//LOG.debug() << "end of parsing" << std::endl;
	return (true);
}

bool	ActiveHTTP::always(int fd) {
	(void)fd;

	// If a request is parsed and a task is still running, the server should not timeout
	if (_response.get_ready() && !_response.get_sent())
		postpone_timeout();
	//sleep(2);
	//size_t i = 0;
	/*LOG.debug() << "----------------- all requests" << std::endl;
	for (std::list<Request>::const_iterator it = _reqs.begin(); it != _reqs.end(); it++) {
		LOG.debug() << "<<< request number " << i++ << std::endl
					<< *it << (*it).get_over() << "//" << (*it).get_head() << std::endl
					<< ">>>" << std::endl;
	}
	LOG.debug() << "----------------- end of all requests" << std::endl;*/

	if (!_request.get_treated_by_middlewares() && _request.get_head() == 6) {
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
	if (_response.get_ready() && !_response.get_sent())
	{
		if (!_response.get_beginning_sent() && _response.get_delegated_to_task()) {
			std::ostringstream os;
			os < _response;
			_write_buffer += os.str();
			LOG.debug() << "Beginning of the request written on the write buffer" << std::endl;
			_response.set_beginning_sent(true);
		}
		if (!_response.get_delegated_to_task())
		{
			std::ostringstream os;
			os << _response;
			_write_buffer += os.str();
			LOG.debug() << "Request totally written on the write buffer" << std::endl;
			_response.set_sent(true);
		}
	}
	if (_response.get_sent()) {
		LOG.debug() << "ActiveHTTP server is reinitialized" << std::endl;
		_request.reinitialize();
		_response.reinitialize();
	}
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

void ActiveHTTP::setServerBlocks(std::vector<ServerBlock> const* server_blocks) {
	_server_blocks = server_blocks;
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

/*void	ActiveHTTP::send_response() {	
	std::ostringstream oss;
	oss << _response;
	_write_buffer += oss.str();
	_request.reinitialize();
	_response.reinitialize();
}*/

void	ActiveHTTP::send_partial_response(const std::string& str) {	
	std::ostringstream oss;
	_write_buffer += str;
}
