#include "ActiveHTTP.hpp"
#include "ActiveServer.hpp"
#include "NIOSelector.hpp"

ActiveHTTP::ActiveHTTP() : ActiveServer() {
}

ActiveHTTP::ActiveHTTP(const ActiveHTTP& src) : ActiveServer(src) {
	*this = src;
}

ActiveHTTP::ActiveHTTP(Socket* socket) : ActiveServer(socket) {
}

ActiveHTTP& ActiveHTTP::operator=(const ActiveHTTP& src) {
	if (this != &src) {
		ActiveServer::operator=(src);
	}
	return (*this);
}

ActiveHTTP::~ActiveHTTP() {
}

void	ActiveHTTP::readable(int fd) {
		try {
			size_t parsed_chars;
			(void)parsed_chars;

			std::ostringstream ss;
			ActiveServer::readable(fd);
			parsed_chars = _req.parse_all(_read_buffer.c_str());
			ss << "<<<" << std::endl;
			ss << _req << std::endl;
			ss << ">>>" << std::endl;
			_write_buffer = ss.str();
			
			//std::cout << "read_buffer: \"" << _read_buffer << "\"" << std::endl;
			//std::cout << "write_buffer: \"" << _write_buffer << "\"" << std::endl;
			_read_buffer = _read_buffer.substr(parsed_chars);
			//std::cout << "read_buffer: \"" << _read_buffer << "\"" << std::endl;
		}
		catch(std::exception &e) {
		}
}
