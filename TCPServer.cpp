#include "TCPServer.hpp"

TCPSocket::TCPSocket() {
}

void TCPSocket::init(struct sockaddr_in &my_addr, short &port) {
	if ((_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		throw std::runtime_error("");
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(port);
	_port = port;
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
	_address = INADDR_ANY;
	if (bind(_fd, (struct sockaddr*)&my_addr, sizeof my_addr) < 0)
	{
		std::ostringstream oss;
		oss << "cannot bind socket to port " << port;
		throw std::runtime_error(oss.str());
	}
	int yes = 1;
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) < 0)
	{
		std::ostringstream oss;
		oss << "setsockopt: unexpected error while setting options for port " << port;
		throw std::runtime_error(oss.str());
	}
	if (::listen(_fd, SOMAXCONN) < 0)
	{
		std::ostringstream oss;
		oss << "Cannot listen on  socket to port " << port;
		throw std::runtime_error(oss.str());
	}

#ifdef DEBUG
	std::cerr << "lol" << std::endl;
#endif
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

void	TCPSocket::listen(short port) {
	if (::listen(_fd, SOMAXCONN) < 0)
	{
		std::ostringstream oss;
		oss << "Cannot listen on  socket to port " << port;
		throw std::runtime_error(oss.str());
	}
}

TCPSocket*	 TCPSocket::accept() const throw (std::runtime_error)
{
	struct sockaddr_storage		address;
	socklen_t					addr_len;

	addr_len = sizeof(address);
	int newfd = ::accept(_fd, (struct sockaddr*)&address, &addr_len);
	if (newfd < 0)
		throw std::runtime_error("accept: error");
	TCPSocket *newSocket = new TCPSocket();
	newSocket->_fd = newfd;
	return (newSocket);
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
	char	tmp[maxlen];
	ssize_t ret = recv(tmp, maxlen, flags);
	return (std::string(tmp, ret));
}

ssize_t TCPSocket::recv(void *buf, int maxlen, int flags) throw (std::runtime_error)
{
	ssize_t ret = ::recv(_fd, buf, maxlen, flags);
	if (ret < 0)
		throw std::runtime_error("recv: error");
	if (ret == 0)
		throw std::runtime_error("recv: remote host closed connection");
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


