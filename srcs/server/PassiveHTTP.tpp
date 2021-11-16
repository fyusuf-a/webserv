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
#include "../utils/Log.hpp"

template<typename T>
Log& PassiveHTTP<T>::LOG = Log::getInstance();

template<typename T>
PassiveHTTP<T>::PassiveHTTP() : PassiveServer<T>() {
	_server_blocks = ServerBlock();
}

template<typename T>
PassiveHTTP<T>::PassiveHTTP(const PassiveHTTP& src) : PassiveServer<T>(src) {
	*this = src;
}

template<typename T>
PassiveHTTP<T>& PassiveHTTP<T>::operator=(const PassiveHTTP& src) {
	if (this != &src) {
		PassiveServer<T>::operator=(src);
		_interface = src._interface;
		_server_blocks = src._server_blocks;
	}
	return *this;
}

template<typename T>
PassiveHTTP<T>::PassiveHTTP(const INetAddress& address, const std::vector<ServerBlock>* server_blocks, bool nonblocking)
	: PassiveServer<T>(address, nonblocking)
	, _interface(address)
	, _server_blocks(server_blocks)
{
}

/*template<typename T>
PassiveHTTP<T>::PassiveHTTP(uint32_t ip, uint16_t port, const std::vector<ServerBlock>* server_blocks, bool nonblocking)
	: PassiveServer<T>(ip, port, nonblocking)
	, _interface(INetAddress(ip, port))
	, _server_blocks(server_blocks) {
	//_server_block = ServerBlock(server_block);
}*/

template<typename T>
PassiveHTTP<T>::~PassiveHTTP() {
}

template<typename T>
bool PassiveHTTP<T>::on_readable(int fd) {
	(void)fd;
	LOG.info() << "New connection on " << this->_socket->getAddress() << std::endl;
	T* activeServer = new T(this->_socket->accept(), _interface, _server_blocks);
	//activeServer->setServerBlocks(_server_blocks);
	LOG.info() << "Transfering connection to " << activeServer->getSocket()->getAddress() << std::endl;
	return (true);
}

#endif
