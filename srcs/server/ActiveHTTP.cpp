#include "ActiveHTTP.hpp"
#include "ActiveServer.hpp"
#include "NIOSelector.hpp"
#include <ctime>

ActiveHTTP::ActiveHTTP() : ActiveServer() {
	time(&_last_time_active);
}

ActiveHTTP::ActiveHTTP(const ActiveHTTP& src) : ActiveServer(src) {
	*this = src;
}

ActiveHTTP::ActiveHTTP(Socket* socket) : ActiveServer(socket) {
	time(&_last_time_active);
}

ActiveHTTP& ActiveHTTP::operator=(const ActiveHTTP& src) {
	if (this != &src) {
		ActiveServer::operator=(src);
		_last_time_active = src._last_time_active;
	}
	return (*this);
}

ActiveHTTP::~ActiveHTTP() {
}

const Request &ActiveHTTP::get_req() const {
	return (_req);
}

time_t const& ActiveHTTP::get_last_time_active() const {
	return _last_time_active;
}

void	ActiveHTTP::on_readable(int fd) {
	size_t				parsed_chars;
	std::ostringstream	ss;
	try {
		ActiveServer::on_readable(fd);
	}
	catch (Socket::ConnectionClosed& e) {
		return ;
	}
	catch(std::exception &e) {
		return ;
	}
	time(&_last_time_active);
	parsed_chars = _req.parse_all(_read_buffer.c_str());
	ss << "<<<" << std::endl;
	ss << _req << std::endl;
	ss << ">>>" << std::endl;
	_write_buffer += ss.str();
	_read_buffer = _read_buffer.substr(parsed_chars);
}

void	ActiveHTTP::always(int fd) {
	(void)fd;
	time_t				now;

	time(&now);
	if (difftime(now, _last_time_active) > TIMEOUT)
	{
		std::cerr << "Connection timed out" << std::endl;
		on_close(fd);
	}
}
