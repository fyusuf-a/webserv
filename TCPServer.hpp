#ifndef TCPSOCKET_HPP
#define TCPSOCKET_HPP

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

typedef int Handle;

class TCPSocket { //: public std::streambuf {

public:

	TCPSocket();
	// Use socket as a server
	TCPSocket(short port);
	//TCPSocket(int fd);
	// Use socket as a client
	TCPSocket(char *address, short port);
	TCPSocket(const TCPSocket&);
	TCPSocket&	operator=(const TCPSocket&);
	virtual 	~TCPSocket();
	void		listen(short port);
	TCPSocket*	accept() const throw (std::runtime_error);
	ssize_t		send(const std::string& message, int flags = 0) throw (std::runtime_error);
	ssize_t		send(const void *msg, int len, int flags = 0) throw (std::runtime_error);
	std::string recv(int maxlen, int flags = 0) throw (std::runtime_error);
	ssize_t		recv(void *buf, int maxlen, int flags = 0) throw (std::runtime_error);

	int		_fd;
	long	_address;
	short	_port;
	long	_client_address;
protected:
	//int				overflow(int);
	//int				underflow();
	//std::streambuf*	setbuf(char*, int, int);
	//int				sync;
	//virtual int		underflow(int c = EOF);

protected:
	void	init(struct sockaddr_in &my_addr, short &port);
};

#endif
