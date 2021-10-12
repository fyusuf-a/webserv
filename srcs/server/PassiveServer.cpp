#include "../../includes/Socket.hpp"
#include "../../includes/PassiveServer.hpp"
#include "../../includes/ActiveServer.hpp"
#include "../../includes/INetAddress.hpp"
#include <cstring>
#include <stdexcept>

PassiveServer::PassiveServer() : Callback() {
	_socket = new Socket();
}

PassiveServer::PassiveServer(const PassiveServer& src) : Callback(src) {
	*this = src;
}

PassiveServer& PassiveServer::operator=(const PassiveServer& src) {
	if (this != &src) {
		Callback::operator=(src);
		_socket = new Socket(*src._socket);
	}
	return *this;
}

PassiveServer::PassiveServer(short port, bool nonblocking) {
	_socket = new Socket(port, nonblocking);
	_socket->listen();
}

PassiveServer::~PassiveServer() {
	delete _socket;
}

void			PassiveServer::readable(int fd) {
	(void)fd;
	Socket* newSock = _socket->accept();
	NIOSelector::getInstance()->add(newSock->getFd(), 
			*static_cast<ActiveServer*>(new ActiveServer(newSock)) , READ | WRITE);
}

void			PassiveServer::writable(int fd) {
	(void)fd;
}

void			PassiveServer::on_close(int fd) {
	(void)fd;
}
