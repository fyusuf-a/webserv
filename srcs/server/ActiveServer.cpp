#include "../../includes/ActiveServer.hpp"

ActiveServer::ActiveServer() {
	_socket = new ActiveSocket();
}

ActiveServer::ActiveServer(const ActiveServer& src) {
	*this = src;
}

ActiveServer& ActiveServer::operator=(const ActiveServer& src) {
	if (this != &src) {
		/* make *this and src equal */
	}
	return (*this);
}

ActiveServer::~ActiveServer() {
}

void ActiveServer::readable(int fd) {
	(void)fd;
	ssize_t max_read = BUFFER_LENGTH - _read_buffer.length();
	char tmp[max_read];
	if (max_read > 0)
		_read_buffer += recv(tmp, max_read);
}

void ActiveServer::writable(int fd) {
	(void)fd;
	if (_write_buffer.empty())
		return ;
	ssize_t sent = send(_write_buffer);
	_write_buffer.substr(0, sent);
	/*size_t len = std::min<size_t>(BUFFER_LENGTH, _write_buffer.length());

	if (len > 0)
	{
		send(_write_buffer.substr(0, len), len);
		_read_buffer = _write_buffer.substr(len);
	}*/
}

void ActiveServer::on_close(int fd) {
	NIOSelector::getInstance()->remove(fd);
	delete (this);
}
