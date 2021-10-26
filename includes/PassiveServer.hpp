#ifndef PASSIVESERVER_HPP
#define PASSIVESERVER_HPP

#include "INetAddress.hpp"
#include "Socket.hpp"
#include "ActiveServer.hpp"
#include "NIOSelector.hpp"
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
class PassiveServer : public NIOSelector::Callback {

public:
	PassiveServer();
	PassiveServer(const PassiveServer&);
	PassiveServer&	operator=(const PassiveServer&);
	PassiveServer(const INetAddress& address, bool nonblocking=true);
	PassiveServer(uint32_t ip, uint16_t port, bool nonblocking=true);
	virtual 		~PassiveServer();

protected:
	Socket			*_socket;
	void			writable(int fd);
	void			readable(int fd);
	void			on_close(int fd);

private:
	void init(const INetAddress& address, bool nonblocking);
};

#ifndef PASSIVESERVER_TPP
#include "../srcs/server/PassiveServer.tpp"
#endif

#endif
