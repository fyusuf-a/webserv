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
			std::ostringstream ss;
			ActiveServer::readable(fd);
			_req.parse_all(_read_buffer);
			ss << "<<<" << std::endl;
			ss << _req << std::endl;
			ss << ">>>" << std::endl;
			_write_buffer = ss.str();
			
			std::cout << "read_buffer: \"" << _read_buffer << "\"" << std::endl;
			std::cout << "write_buffer: \"" << _write_buffer << "\"" << std::endl;

			//size_t write_len = _write_buffer.length();
			//size_t read_len = _read_buffer.length();
			//_write_buffer += _read_buffer;
			//for (size_t i = write_len; i < write_len + read_len; i++)
				//_write_buffer[i] = _write_buffer[i];
			//_read_buffer = "";
		}
		catch(std::exception &e) {
		}
}
