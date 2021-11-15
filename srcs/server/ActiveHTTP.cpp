#include "ActiveHTTP.hpp"
#include "ActiveServer.hpp"
#include "NIOSelector.hpp"
#include "../utils/Log.hpp"
#include <ctime>
#include <ostream>

Log& ActiveHTTP::LOG = Log::getInstance();

ActiveHTTP::ActiveHTTP() : ActiveServer(), _still_parsing(false), _server_blocks(NULL) {
	time(&_last_time_active);
}

ActiveHTTP::ActiveHTTP(const ActiveHTTP& src) : ActiveServer(src), _still_parsing(src._still_parsing), _server_blocks(src._server_blocks) {
	*this = src;
}

ActiveHTTP::ActiveHTTP(Socket* socket, INetAddress const& interface, std::vector<ServerBlock> const* server_blocks)
													: ActiveServer(socket)
													, _still_parsing(false)
													, _interface(interface)
													, _server_blocks(server_blocks)
{
	time(&_last_time_active);
}

ActiveHTTP::ActiveHTTP(Socket* socket)
													: ActiveServer(socket)
													, _still_parsing(false)
													, _server_blocks(NULL)
{
	time(&_last_time_active);
}

ActiveHTTP& ActiveHTTP::operator=(const ActiveHTTP& src) {
	if (this != &src) {
		ActiveServer::operator=(src);
		_still_parsing = false;
		_last_time_active = src._last_time_active;
		_interface = src._interface;
		_server_blocks = src._server_blocks;
	}
	return (*this);
}

ActiveHTTP::~ActiveHTTP() {
}

const std::list<Request> &ActiveHTTP::get_reqs() const {
	return (_reqs);
}

time_t const& ActiveHTTP::get_last_time_active() const {
	return _last_time_active;
}

bool	ActiveHTTP::on_readable(int fd) {
	if (ActiveServer::on_readable(fd) == false)
		return (false);
	std::ostringstream	ss;

	time(&_last_time_active);
	std::cout << "readbuffer avant parsing:" << std::endl
				  << "(" << _read_buffer << ")" << std::endl;
	while (1) {
		if (!_still_parsing)
			_reqs.resize(_reqs.size() + 1);
		_reqs.back().set_over(true);
		while (_reqs.back().get_head() < 6 && _reqs.back().get_over()) {
			_reqs.back().parse(_read_buffer);
		}
		_still_parsing = _reqs.back().get_over() == 0 ? 1 : 0;
		if (_read_buffer == "" || !_reqs.back().get_over())
			break ;
	}

	size_t i = 0;
	for (std::list<Request>::const_iterator it = _reqs.begin(); it != _reqs.end(); it++) {
		LOG.debug() << "<<< request number " << i++ << std::endl
					<< *it << (*it).get_over() << "//" << (*it).get_head() << std::endl
					<< ">>>" << std::endl;
	}
	std::cout << "readbuffer after parsing: " << std::endl
			  << "(" << _read_buffer << ")" << std::endl;
	LOG.debug() << "end of parsing" << std::endl;
	return (true);
}

bool	ActiveHTTP::always(int fd) {
	(void)fd;
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

std::vector<ServerBlock> const* ActiveHTTP::getServerBlocks() const {
	return _server_blocks;
}

INetAddress ActiveHTTP::getInterface() const {
	return _interface;
}

void ActiveHTTP::setServerBlocks(std::vector<ServerBlock> const* server_blocks) {
	_server_blocks = server_blocks;
}
