#include "ActiveServer.hpp"
#include "NIOSelector.hpp"
#include "../utils/Log.hpp"

Log& ActiveServer::LOG = Log::getInstance();

ActiveServer::ActiveServer() : Callback(), _status(false) {
	_socket = new Socket();
	NIOSelector::getInstance().add(_socket->getFd(), *this, READ | WRITE);
}

ActiveServer::ActiveServer(const ActiveServer& src) : Callback(src) {
	*this = src;
}

ActiveServer::ActiveServer(Socket* socket) {
	_socket = socket;
	NIOSelector::getInstance().add(_socket->getFd(), *this, READ | WRITE);
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
	std::ostringstream oss;
	if (INetAddress* peer = _socket->getPeer())
		oss << " with " << peer->getAddress();
	LOG.info() << "Connection closed" << oss.str() << " on "
		<< _socket->getInterface() << " (fd " << _socket->getFd() << ")" << std::endl;
	NIOSelector::getInstance().remove(_socket->getFd());
	delete _socket;
}

Socket *ActiveServer::getSocket() const {
	return _socket;
}

void	ActiveServer::setStatus(bool val) {
	_status = val;
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
		if (_status)
			return on_close(fd);
	}
	catch (std::exception& e) {
		LOG.error() << "An error occured while using send" << std::endl;
		return on_close(fd);
	}
	_write_buffer = _write_buffer.substr(sent);
	return (true);
}

bool ActiveServer::on_close(int) {
	delete (this);
	return (false);
}

bool ActiveServer::always(int) {
	return (true);
}
