#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "INetAddress.hpp"
#include "IPAddress.hpp"
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
	class ConnectionClosed : public std::exception {
		const char* what() const throw() {
			return "Connection Closed";
		}
	};

	Socket();
	// Throws a std::runtime_error if initialization went wrong
	Socket(const INetAddress& address, bool nonblocking=true);
	Socket(const IPAddress& ip, uint16_t port, bool nonblocking=true);
	Socket(const Socket&);
	Socket&	operator=(const Socket&);
	virtual 		~Socket();
	// Throws a std::runtime_error if listen was impossible
	void			listen();
	// Throws a std::runtime_error if accept was impossible
	Socket*	accept() const;
	// Throws a std::runtime_error if send went wrong, returns the number of
	// byte sent otherwise
	ssize_t			send(const std::string& message, int flags = 0);
	// Throws a std::runtime_error if send went wrong, returns the number of
	// byte sent otherwise
	ssize_t			send(const void *msg, int len, int flags = 0);
	// Throws a std::runtime_error if recv went wrong, or a ConnectionClosed
	// exception if the connection was closed
	std::string 	recv(int maxlen, int flags = 0);
	// Throws a std::runtime_error if recv went wrong, or a ConnectionClosed
	// exception if the connection was closed
	ssize_t			recv(void *buf, int maxlen, int flags = 0);

	int				getFd() const;
	INetAddress 	getAddress() const;
	void			setFd(const int&);
	void			setAddress(const INetAddress&);
	void			setPort(u_int16_t port);

protected:
	int		_fd;
	INetAddress	_address;

private:
	void	init(struct sockaddr_in &my_addr, short &port);
};

#endif
