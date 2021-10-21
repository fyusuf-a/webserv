#ifndef PASSIVESERVER_TPP
#define PASSIVESERVER_TPP

#include "../includes/Socket.hpp"
#include "../includes/ActiveServer.hpp"
#include "../includes/PassiveServer.hpp"
#include "../includes/NIOSelector.hpp"
#include "PassiveServer.hpp"
#include "PassiveHTTP.hpp"
#include "serverBlock.hpp"
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
PassiveHTTP<T>::PassiveHTTP(uint32_t ip, uint16_t port, const ServerBlock& server_block, bool nonblocking) : PassiveServer<T>(ip, port, nonblocking){
	_server_block = ServerBlock(server_block);
}

template<typename T> PassiveHTTP<T>::~PassiveHTTP() {
}

template<typename T> void PassiveHTTP<T>::readable(int fd) {
	try {
		ActiveServer::readable(fd);
		size_t write_len = _write_buffer.length(); size_t read_len = _read_buffer.length();
		_write_buffer += _read_buffer;
		for (size_t i = write_len; i < write_len + read_len; i++)
			_write_buffer[i] = F(_write_buffer[i]);
		_read_buffer = "";
	}
	catch(std::exception &e) {
	}
}

#endif
