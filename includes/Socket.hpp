#ifndef SOCKET_HPP
#define SOCKET_HPP

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

class Socket { //: public std::streambuf {

public:
	Socket();
	Socket(short port, bool nonblocking=true);
	Socket(const Socket&);
	Socket&	operator=(const Socket&);
	virtual 		~Socket();
	void			listen();
	Socket*	accept() const throw (std::runtime_error);
	ssize_t			send(const std::string& message, int flags = 0) throw (std::runtime_error);
	ssize_t			send(const void *msg, int len, int flags = 0) throw (std::runtime_error);
	std::string 	recv(int maxlen, int flags = 0) throw (std::runtime_error);
	ssize_t			recv(void *buf, int maxlen, int flags = 0) throw (std::runtime_error);

	int				getFd() const;
	INetAddress 	getAddress() const;
	void			setFd(const int&);
	void			setAddress(const INetAddress&);
	void			setPort(u_int16_t port);
	//newSocket->_address.setPort((*reinterpret_cast<struct sockaddr_in*>(&address)).sin_port);

protected:
	int		_fd;
	INetAddress	_address;

	//long	_address;
	//short	_port;
	//long	_client_address;

private:
	void	init(struct sockaddr_in &my_addr, short &port);
};

#endif
