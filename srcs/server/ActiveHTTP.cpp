#include "ActiveHTTP.hpp"
#include "ActiveServer.hpp"
#include "NIOSelector.hpp"
#include "../utils/Log.hpp"
#include <ctime>
#include <ostream>
#include <sstream>
#include "../http/Response/Response.hpp"

Log& ActiveHTTP::LOG = Log::getInstance();

ActiveHTTP::ActiveHTTP() : ActiveServer(), _still_parsing(true), _server_blocks(NULL), _chain(NULL) {
	time(&_last_time_active);
}

ActiveHTTP::ActiveHTTP(const ActiveHTTP& src) : ActiveServer(src), _still_parsing(true), _server_blocks(src._server_blocks), _chain(NULL) {
	*this = src;
}

ActiveHTTP::ActiveHTTP(Socket* socket, INetAddress const& interface, std::vector<ServerBlock> const* server_blocks)
													: ActiveServer(socket)
													, _still_parsing(true)
													, _interface(interface)
													, _server_blocks(server_blocks)
													, _chain(NULL)
{
	time(&_last_time_active);
}

ActiveHTTP::ActiveHTTP(Socket* socket)
													: ActiveServer(socket)
													, _still_parsing(true)
													, _server_blocks(NULL)
													, _chain(NULL)
{
	time(&_last_time_active);
}

ActiveHTTP& ActiveHTTP::operator=(const ActiveHTTP& src) {
	if (this != &src) {
		ActiveServer::operator=(src);
		_still_parsing = src._still_parsing;
		_last_time_active = src._last_time_active;
		_interface = src._interface;
		_server_blocks = src._server_blocks;
	}
	return (*this);
}

ActiveHTTP::~ActiveHTTP() {
}

bool	ActiveHTTP::on_readable(int fd) {
	time(&_last_time_active);
	if (_closing)
		return (false);
	if (!ActiveServer::on_readable(fd)) {
		_closing = true;
		return (false);
	}
	std::ostringstream	ss;

	std::cout << "readbuffer avant parsing:" << std::endl
				  << "(" << _read_buffer << ")" << std::endl;

	while (1) {
		if (!_still_parsing)
		{
			_reqs.push_back(_parsed_request);
			_parsed_request.reinitialize();
			_still_parsing = true;
		}
		_parsed_request.set_over(true);
		if (_read_buffer == "" || !_parsed_request.get_over())
			break ;
		while (_parsed_request.get_head() < 6 && _parsed_request.get_over())
			_parsed_request.parse(_read_buffer);
		_still_parsing = !_parsed_request.get_over();
	}

	LOG.debug() << "----------------- parsed request" << std::endl;
	std::cout << _parsed_request << std::endl;

	std::cout << "readbuffer after parsing: " << std::endl
			  << "(" << _read_buffer << ")" << std::endl;
	LOG.debug() << "end of parsing" << std::endl;
	return (true);
}

bool	ActiveHTTP::always(int fd) {
	(void)fd;

	sleep(2);
	size_t i = 0;
	LOG.debug() << "----------------- all requests" << std::endl;
	for (std::list<Request>::const_iterator it = _reqs.begin(); it != _reqs.end(); it++) {
		LOG.debug() << "<<< request number " << i++ << std::endl
					<< *it << (*it).get_over() << "//" << (*it).get_head() << std::endl
					<< ">>>" << std::endl;
	}
	LOG.debug() << "----------------- end of all requests" << std::endl;

	if (!_reqs.empty())
	{
		if (!_reqs.front().get_treated_by_middlewares())
		{
			Request* req = &_reqs.front();
			_chain = new MiddlewareChain(this, req, &_resp);
			req->set_treated_by_middlewares(true);
			(*_chain)();
		}
	}
	if (_resp.get_ready())
		send_response();
	if (!check_timeout(fd))
		return (false);
	return (true);
}

bool	ActiveHTTP::on_close(int fd) {
	_closing = true;
	if (_reqs.empty())
		ActiveServer::on_close(fd);
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

const std::list<Request> &ActiveHTTP::get_reqs() const {
	return (_reqs);
}

const Response &ActiveHTTP::get_resp() const {
	return (_resp);
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

void	ActiveHTTP::send_response() {
	_reqs.pop_front();
	std::ostringstream oss;
	oss << _resp;
	_write_buffer += oss.str();
	_resp.reinitialize();
}
