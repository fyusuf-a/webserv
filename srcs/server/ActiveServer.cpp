#include "ActiveServer.hpp"
#include "NIOSelector.hpp"
#include "../utils/Log.hpp"

Log& ActiveServer::LOG = Log::getInstance();

ActiveServer::ActiveServer() : Callback(), _closing(false) {
	_socket = new Socket();
	NIOSelector::getInstance().add(_socket->getFd(), *this, READ | WRITE);
}

ActiveServer::ActiveServer(const ActiveServer& src) : Callback(src) {
	*this = src;
}

ActiveServer::ActiveServer(Socket* socket) : _closing(false) {
	_socket = socket;
	NIOSelector::getInstance().add(_socket->getFd(), *this, READ | WRITE);
}

ActiveServer& ActiveServer::operator=(const ActiveServer& src) {
	if (this != &src) {
		Callback::operator=(src);
		_write_buffer = std::string(src._write_buffer);
		_read_buffer = std::string(src._read_buffer);
		_socket = new Socket(*src._socket);
		_closing = src._closing;
	}
	return (*this);
}

ActiveServer::~ActiveServer() {
	LOG.info() << "Connection closed with " << _socket->getInterface() << " (fd " << _socket->getFd() << ")" << std::endl;
	delete _socket;
}

Socket *ActiveServer::getSocket() {
	return _socket;
}

bool ActiveServer::on_readable(int fd) {
	if (BUFFER_LENGTH > 0)
	{
		try {
			_read_buffer += _socket->recv(BUFFER_LENGTH);
		}
		catch (Socket::ConnectionClosed& e) {
			on_close(fd);
			return (false);
		}
		catch (std::exception& e) {
			LOG.error() << "An error occured while using recv" << std::endl;
			on_close(fd);
			return (false);
		}
	}
	return (true);
}

bool ActiveServer::on_writable(int fd) {
	(void)fd;
	ssize_t sent;
	if (_write_buffer.empty())
		return (true);
	try {
		sent = _socket->send(_write_buffer);
	}
	catch (std::exception& e) {
		LOG.error() << "An error occured while using send" << std::endl;
		on_close(fd);
		return (false);
	}
	_write_buffer = _write_buffer.substr(sent);
	return (true);
}

bool ActiveServer::on_close(int fd) {
	NIOSelector::getInstance().remove(fd);
	delete (this);
	return (false);
}

bool ActiveServer::always(int) {
	return (true);
}
