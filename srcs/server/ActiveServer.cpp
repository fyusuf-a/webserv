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
	std::cerr << "Connection closed with " << _socket->getAddress() << std::endl;
#endif
	delete _socket;
}

Socket *ActiveServer::getSocket() {
	return _socket;
}

void ActiveServer::readable(int fd) {
	(void)fd;
	ssize_t max_read = BUFFER_LENGTH - _read_buffer.length();
	if (max_read > 0)
	{
		try {
			_read_buffer += _socket->recv(max_read);
		}
		catch (Socket::ConnectionClosed& e) {
			on_close(fd);
		}
		catch (std::exception& e) {
			std::cerr << "An error occured while using recv" << std::endl;
			on_close(fd);
		}
	}
}

void ActiveServer::writable(int fd) {
	(void)fd;
	if (_write_buffer.empty())
		return ;
	try {
		ssize_t sent = _socket->send(_write_buffer);
		_write_buffer = _write_buffer.substr(sent);
	}
	catch (std::exception& e) {
		std::cerr << "An error occured while using send" << std::endl;
		on_close(fd);
	}
}

void ActiveServer::on_close(int fd) {
	(void)fd;
	NIOSelector::getInstance()->remove(fd);
	delete (this);
}
