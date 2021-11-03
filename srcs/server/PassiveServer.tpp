#ifndef PASSIVESERVER_TPP
#define PASSIVESERVER_TPP

#include "PassiveServer.hpp"

template<typename T>
Log& PassiveServer<T>::LOG = Log::getInstance();

template<typename T>
PassiveServer<T>::PassiveServer() : Callback() {
	_socket = new Socket();
	NIOSelector::getInstance().add(_socket->getFd(), *this, READ);
}

template<typename T>
PassiveServer<T>::PassiveServer(const PassiveServer& src) : Callback(src) {
	*this = src;
}

template<typename T>
PassiveServer<T>& PassiveServer<T>::operator=(const PassiveServer& src) {
	if (this != &src) {
		Callback::operator=(src);
		_socket = new Socket(*src._socket);
	}
	return *this;
}

template<typename T>
void PassiveServer<T>::init(const INetAddress& address, bool nonblocking) {
	_socket = new Socket(address, nonblocking);
	_socket->listen();
	NIOSelector::getInstance().add(_socket->getFd(), *this, READ);
}

template<typename T>
PassiveServer<T>::PassiveServer(const INetAddress& address, bool nonblocking) {
	init(address, nonblocking);
}

template<typename T>
PassiveServer<T>::PassiveServer(uint32_t ip, uint16_t port, bool nonblocking) {
	INetAddress address(ip, port);
	init(address, nonblocking);
}

template<typename T> PassiveServer<T>::~PassiveServer() {
	NIOSelector::getInstance().remove(_socket->getFd());
	delete _socket;
}

template<typename T>
bool			PassiveServer<T>::on_readable(int fd) {
	(void)fd;
	Log::getInstance().debug() << "New connection on passive server" << std::endl;
	new T(_socket->accept());
	return (true);
}

template<typename T>
bool			PassiveServer<T>::on_writable(int fd) {
	(void)fd;
	return (true);
}

template<typename T>
bool			PassiveServer<T>::on_close(int fd) {
	(void)fd;
	return (true);
}

template<typename T>
bool			PassiveServer<T>::always(int fd) {
	(void)fd;
	return (true);
}

#endif
