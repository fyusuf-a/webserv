#ifndef PASSIVESOCKET_HPP
#define PASSIVESOCKET_HPP

#include "INetAddress.hpp"
#include "ActiveSocket.hpp"
#include "Socket.hpp"
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

class PassiveSocket : public Socket {

public:
	PassiveSocket();
	PassiveSocket(short port, bool nonblocking=true);
	PassiveSocket(const PassiveSocket&);
	PassiveSocket&	operator=(const PassiveSocket&);
	virtual 		~PassiveSocket();
	void			listen();
	ActiveSocket*	accept() const throw (std::runtime_error);
};

#endif
