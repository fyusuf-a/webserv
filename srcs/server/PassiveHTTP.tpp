#ifndef PASSIVEHTTP_TPP
#define PASSIVEHTTP_TPP

#include "Socket.hpp"
#include "ActiveServer.hpp"
#include "PassiveServer.hpp"
#include "PassiveHTTP.hpp"
#include "NIOSelector.hpp"
#include "../parsingConf/serverBlock.hpp"
#include <cctype>
#include <arpa/inet.h>

template<typename T>
PassiveHTTP<T>::PassiveHTTP() : PassiveServer<T>() {
	_server_block = ServerBlock();
}

template<typename T>
PassiveHTTP<T>::PassiveHTTP(const PassiveHTTP& src) : PassiveServer<T>(src) {
	*this = src;
}

template<typename T>
PassiveHTTP<T>& PassiveHTTP<T>::operator=(const PassiveHTTP& src) {
	if (this != &src) {
		PassiveServer<T>::operator=(src);
		_server_block = ServerBlock(src._server_block);
	}
	return *this;
}

template<typename T>
PassiveHTTP<T>::PassiveHTTP(const INetAddress& address, const ServerBlock& server_block, bool nonblocking) : PassiveServer<T>(address, nonblocking){
	_server_block = ServerBlock(server_block);
}

template<typename T>
PassiveHTTP<T>::PassiveHTTP(uint32_t ip, uint16_t port, const ServerBlock& server_block, bool nonblocking) : PassiveServer<T>(ip, port, nonblocking) {
	_server_block = ServerBlock(server_block);
}

template<typename T> PassiveHTTP<T>::~PassiveHTTP() {
}

template<typename T> void PassiveHTTP<T>::on_readable(int fd) {
	(void)fd;
#ifdef DEBUG
	std::cerr << "New connection on passive HTTP server" << std::endl;
#endif
	new T(this->_socket->accept());
}

#endif
