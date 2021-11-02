#include "ActiveServer.hpp"
#include "NIOSelector.hpp"
#include "../utils/Log.hpp"

ActiveServer::ActiveServer() : Callback() {
	_socket = new Socket();
	NIOSelector::getInstance()->add(_socket->getFd(), *this, READ | WRITE);
}

ActiveServer::ActiveServer(const ActiveServer& src) : Callback(src) {
	*this = src;
}

ActiveServer::ActiveServer(Socket* socket) {
	_socket = socket;
	NIOSelector::getInstance()->add(_socket->getFd(), *this, READ | WRITE);
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
	Log<>(INFO) << "Connection closed with " << _socket->getAddress();
	NIOSelector::getInstance()->remove(_socket->getFd());
	delete _socket;
}

Socket *ActiveServer::getSocket() {
	return _socket;
}

bool ActiveServer::on_readable(int fd) {
	(void)fd;
	ssize_t max_read = BUFFER_LENGTH - _read_buffer.length();
	if (max_read > 0)
	{
		try {
			_read_buffer += _socket->recv(max_read);
		}
		catch (Socket::ConnectionClosed& e) {
			on_close(fd);
			return (false);
		}
		catch (std::exception& e) {
			Log<>(ERROR) << "An error occured while using recv";
			on_close(fd);
			return (false);
		}
	}
	return (true);
}

bool ActiveServer::on_writable(int fd) {
	(void)fd;
	if (_write_buffer.empty())
		return (true);
	try {
		ssize_t sent = _socket->send(_write_buffer);
		_write_buffer = _write_buffer.substr(sent);
	}
	catch (std::exception& e) {
		Log<>(ERROR) << "An error occured while using send";
		on_close(fd);
		return (false);
	}
	return (true);
}

bool ActiveServer::on_close(int fd) {
	(void)fd;
	delete (this);
	return (false);
}
