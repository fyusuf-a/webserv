#ifndef PASSIVEHTTP_HPP
#define PASSIVEHTTP_HPP

#include "INetAddress.hpp"
#include "Socket.hpp"
#include "ActiveServer.hpp"
#include "PassiveServer.hpp"
#include "NIOSelector.hpp"
#include "serverBlock.hpp"
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
	PassiveHTTP();
	PassiveHTTP(const PassiveHTTP&);
	PassiveHTTP&	operator=(const PassiveHTTP&);
	PassiveHTTP(const INetAddress& address, const ServerBlock& server_block, bool nonblocking=true);
	PassiveHTTP(uint32_t ip, uint16_t port, const ServerBlock& server_block, bool nonblocking=true);
	virtual 		~PassiveHTTP();

protected:
	ServerBlock			_server_block;
	void				readable(int fd);
};

#ifndef PASSIVEHTTP_TPP
	#include "../srcs/server/PassiveHTTP.tpp"
#endif

#endif
