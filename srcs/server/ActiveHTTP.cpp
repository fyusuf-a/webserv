#include "ActiveHTTP.hpp"
#include "ActiveServer.hpp"
#include "NIOSelector.hpp"
#include "../utils/Log.hpp"
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

bool	ActiveHTTP::on_readable(int fd) {
	size_t				parsed_chars;
	std::ostringstream	ss;

	if (ActiveServer::on_readable(fd) == false)
		return (false);
	time(&_last_time_active);
	parsed_chars = _req.parse_all(_read_buffer.c_str());
	ss << "<<<" << std::endl;
	ss << _req << std::endl;
	ss << ">>>" << std::endl;
	_write_buffer += ss.str();
	_read_buffer = _read_buffer.substr(parsed_chars);
	return (true);
}

bool	ActiveHTTP::always(int fd) {
	(void)fd;
	time_t				now;

	time(&now);
	if (difftime(now, _last_time_active) > TIMEOUT)
	{
		Log<>(INFO) << "Connection timed out";
		on_close(fd);
		return (false);
	}
	return (true);
}
