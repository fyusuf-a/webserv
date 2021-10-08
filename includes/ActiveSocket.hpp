#ifndef ACTIVESOCKET_HPP
#define ACTIVESOCKET_HPP

#include "INetAddress.hpp"
#include "NIOSelector.hpp"
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

#define BUFFER_LENGTH 4096

class ActiveSocket : public Socket, public NIOSelector::Callback { //: public std::streambuf {

public:
	ActiveSocket();
	ActiveSocket(short port, bool nonblocking=true);
	ActiveSocket(char *address, short port);
	ActiveSocket(const ActiveSocket&);
	ActiveSocket&	operator=(const ActiveSocket&);
	virtual 		~ActiveSocket();
	ssize_t			send(const std::string& message, int flags = 0);
	ssize_t			send(const void *msg, ssize_t len, int flags = 0);
	/*std::string 	recv(ssize_t maxlen, int flags = 0);*/
	ssize_t			recv(void *buf, ssize_t maxlen, int flags = 0);

	void			readable(int fd);
	void			writable(int fd);
	void			on_close(int fd);

protected:
	std::string	_write_buffer;
	std::string	_read_buffer;
};

#endif
