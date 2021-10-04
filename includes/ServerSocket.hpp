#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include "INetAddress.hpp"
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

class ServerSocket { //: public std::streambuf {

public:

	ServerSocket();
	// Use socket as a server
	ServerSocket(short port, bool nonblocking=true);
	//ServerSocket(int fd);
	// Use socket as a client
	ServerSocket(char *address, short port);
	ServerSocket(const ServerSocket&);
	ServerSocket&	operator=(const ServerSocket&);
	virtual 		~ServerSocket();
	void			listen();
	ServerSocket*	accept() const throw (std::runtime_error);
	ssize_t			send(const std::string& message, int flags = 0) throw (std::runtime_error);
	ssize_t			send(const void *msg, int len, int flags = 0) throw (std::runtime_error);
	std::string 	recv(int maxlen, int flags = 0) throw (std::runtime_error);
	ssize_t			recv(void *buf, int maxlen, int flags = 0) throw (std::runtime_error);

	int			getFd() const;

private:
	int		_fd;
	INetAddress	_address;

	//long	_address;
	//short	_port;
	//long	_client_address;

protected:
	void	init(struct sockaddr_in &my_addr, short &port);
};

#endif
