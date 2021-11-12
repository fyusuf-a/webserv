#ifndef PASSIVEHTTP_HPP
#define PASSIVEHTTP_HPP

#include "../ipaddress/INetAddress.hpp"
#include "Socket.hpp"
#include "ActiveServer.hpp"
#include "PassiveServer.hpp"
#include "NIOSelector.hpp"
#include "../parsingConf/serverBlock.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <stdexcept>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <stdexcept>

template<typename T>
class PassiveHTTP : public PassiveServer<T> {

public:
	static Log& LOG;

	PassiveHTTP();
	PassiveHTTP(const PassiveHTTP&);
	PassiveHTTP&	operator=(const PassiveHTTP&);
	PassiveHTTP(const INetAddress& address, const std::vector<ServerBlock>* server_blocks, bool nonblocking=true);
	//PassiveHTTP(uint32_t ip, uint16_t port, const std::vector<ServerBlock>* server_blocks, bool nonblocking=true);
	virtual 		~PassiveHTTP();

protected:
	INetAddress						_interface;
	std::vector<ServerBlock> const*	_server_blocks;
	bool							on_readable(int fd);
};

#ifndef PASSIVEHTTP_TPP
	#include "PassiveHTTP.tpp"
#endif

#endif
