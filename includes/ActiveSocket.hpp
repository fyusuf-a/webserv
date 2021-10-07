#ifndef ACTIVESOCKET_HPP
#define ACTIVESOCKET_HPP

#include "INetAddress.hpp"
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

class ActiveSocket : public Socket { //: public std::streambuf {

public:

	ActiveSocket();
	ActiveSocket(short port, bool nonblocking=true);
	ActiveSocket(char *address, short port);
	ActiveSocket(const ActiveSocket&);
	ActiveSocket&	operator=(const ActiveSocket&);
	virtual 		~ActiveSocket();
	ssize_t			send(const std::string& message, int flags = 0) throw (std::runtime_error);
	ssize_t			send(const void *msg, int len, int flags = 0) throw (std::runtime_error);
	std::string 	recv(int maxlen, int flags = 0) throw (std::runtime_error);
	ssize_t			recv(void *buf, int maxlen, int flags = 0) throw (std::runtime_error);
};

#endif
