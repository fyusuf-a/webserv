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

typedef int Handle;

class TCPSocket : public std::streambuf {

public:
	TCPSocket();
	// Use socket as a server
	TCPSocket(short port);
	TCPSocket(int fd);
	// Use socket as a client
	TCPSocket(char *address, short port);
	TCPSocket(const TCPSocket&);
	TCPSocket&	operator=(const TCPSocket&);
	virtual 	~TCPSocket();
	TCPSocket*	accept() const throw (std::runtime_error);
	ssize_t		send(const std::string& message, int flags = 0) throw (std::runtime_error);
	ssize_t		send(const void *msg, int len, int flags = 0) throw (std::runtime_error);
	ssize_t 	recv(void *buf, int len, int maxlen, int flags = 0) throw (std::runtime_error);

protected:
	//int				overflow(int);
	//int				underflow();
	//std::streambuf*	setbuf(char*, int, int);
	//int				sync;
	//virtual int		underflow(int c = EOF);

protected:
	void	init(struct sockaddr_in &my_addr, short &port);
	int		_fd;
	//short	_port;
};

TCPSocket::TCPSocket() {
}

TCPSocket::TCPSocket(int fd) : _fd(fd) {
}

void TCPSocket::init(struct sockaddr_in &my_addr, short &port) {
	if ((_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		throw std::runtime_error("");
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = port;
	memset(my_addr.sin_zero, '\0', sizeof my_addr.sin_zero);
}

TCPSocket::TCPSocket(short port) { //:	_port(port)  {
	struct sockaddr_in my_addr;

	try {
		init(my_addr, port);
		//init(my_addr, _port);
	}
	catch (std::runtime_error& e) {
		std::ostringstream oss;
		oss << "Cannot initialize socket (on port " << port;
		throw std::runtime_error(oss.str());
	}
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(_fd, (struct sockaddr*)&my_addr, sizeof my_addr) < 0)
	{
		std::ostringstream oss;
		oss << "cannot bind socket to port " << port;
		throw std::runtime_error(oss.str());
	}
	int yes = 1;
	if (setsockopt(_fd,  SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) < 0)
	{
		std::ostringstream oss;
		oss << "setsockopt: unexpected error while setting options for port " << port;
		throw std::runtime_error(oss.str());
	}
	if (listen(_fd, SOMAXCONN) < 0)
	{
		std::ostringstream oss;
		oss << "Cannot listen on  socket to port " << port;
		throw std::runtime_error(oss.str());
	}
}


// Examples for address : "90,.12.110.57", "127.0.0.1", etc.
TCPSocket::TCPSocket(char *address, short port) { //:	_port(port)  {
	struct sockaddr_in my_addr;

	try {
		init(my_addr, port);
		//init(my_addr, _port);
	}
	catch (std::runtime_error& e) {
		std::ostringstream oss;
		oss << "Cannot initialize socket (on port " << port << ", on address " << address;
		throw std::runtime_error(oss.str());
	}
	// Code my own inet_pton
	inet_pton(AF_INET, address, &(my_addr.sin_addr));
	memset(my_addr.sin_zero, '\0', sizeof my_addr.sin_zero);
	if (connect(_fd, (struct sockaddr*)&my_addr, sizeof my_addr) < 0)
	{
		std::ostringstream oss;
		oss << "Cannot connect socket to address " << address << "on port " << port;
		throw std::runtime_error(oss.str());
	}
}

TCPSocket::~TCPSocket() {
	close(_fd);
}

TCPSocket*	 TCPSocket::accept() const throw (std::runtime_error)
{
	struct sockaddr_storage*	address;
	socklen_t					addr_len;

	addr_len = sizeof(address);
	int newfd = ::accept(_fd, (struct sockaddr*)address, &addr_len);
	if (newfd < 0)
		throw std::runtime_error("accept: error");
	return (new TCPSocket(newfd));
}

ssize_t TCPSocket::send(const std::string& message, int flags) throw (std::runtime_error)
{
	return ::send(_fd, message.c_str(), message.length(), flags);
}

ssize_t TCPSocket::send(const void *msg, int len, int flags) throw (std::runtime_error)
{
	ssize_t ret = ::send(_fd, msg, len, flags);
	if (ret < 0)
		throw std::runtime_error("send: error");
	return ret;
}

std::string TCPSocket::recv(int maxlen, int flags) throw (std::runtime_error)
{
	char *tmp = NULL;
	if (!(tmp = malloc(maxlen))
		throw std::runtime_error("malloc: error");


}

ssize_t TCPSocket::recv(void *buf, int len, int maxlen, int flags) throw (std::runtime_error)
{
	ssize_t ret = ::recv(_fd, buf, len, flags);
	if (ret == 0)
		throw std::runtime_error("recv: error");
	return (ret);
}


/*int		TCPSocket::underflow(int_type c) {
	if (!gptr())
		return EOF;
	if (gptr() < egptr())
		return (unsigned char)*gptr();
	recv(_fd, buf, 12, 0);

	}
}*/



#endif
