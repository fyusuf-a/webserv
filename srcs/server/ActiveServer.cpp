#include "../../includes/ActiveServer.hpp"
#include "../../includes/NIOSelector.hpp"

ActiveServer::ActiveServer() : Callback() {
	_socket = new Socket();
}

ActiveServer::ActiveServer(const ActiveServer& src) : Callback(src) {
	*this = src;
}

ActiveServer::ActiveServer(Socket* socket) {
	_socket = socket;
}

ActiveServer& ActiveServer::operator=(const ActiveServer& src) {
	if (this != &src) {
		Callback::operator=(src);
		_write_buffer = std::string(src._write_buffer);
		_read_buffer = std::string(src._read_buffer);
		_socket = new Socket(*src._socket);
	}
	return (*this);
}

ActiveServer::~ActiveServer() {
#ifdef DEBUG
	std::cerr << "Connection closed with " << _address << std::endl;
#endif
	delete _socket;
}

void ActiveServer::readable(int fd) {
	(void)fd;
	ssize_t max_read = BUFFER_LENGTH - _read_buffer.length();
	if (max_read > 0)
	{
		char tmp[max_read];
		_read_buffer += _socket->recv(tmp, max_read);
	}
}

void ActiveServer::writable(int fd) {
	(void)fd;
	if (_write_buffer.empty())
		return ;
	ssize_t sent = _socket->send(_write_buffer);
	_write_buffer.substr(0, sent);
}

void ActiveServer::on_close(int fd) {
	NIOSelector::getInstance()->remove(fd);
	delete (this);
}
