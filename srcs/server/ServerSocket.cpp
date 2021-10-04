#include "../../includes/ServerSocket.hpp"
#include "../../includes/INetAddress.hpp"

ServerSocket::ServerSocket() {
}

ServerSocket::ServerSocket(short port, bool nonblocking) { //:	_port(port)  {
	_address = INetAddress(INADDR_ANY, port);
	if ((_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::ostringstream oss;
		oss << "Cannot initialize socket (address " << _address << ')';
		throw std::runtime_error(oss.str());
	}
	int yes = 1;
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) < 0)
	{
		std::ostringstream oss;
		oss << "setsockopt: unexpected error while setting socket options (address: " << _address << ')';
		throw std::runtime_error(oss.str());
	}
	if (nonblocking)
	{
		if (fcntl(_fd, F_SETFL, O_NONBLOCK) < 0)
		{
			std::ostringstream oss;
			oss << "cannot set socket to be not blocking (address: " << _address << ')';
			throw std::runtime_error(oss.str());
		}
	}
	struct sockaddr_in my_struct = _address.getAddress();
	if (bind(_fd, (struct sockaddr*)&my_struct, sizeof my_struct) < 0)
	{
		std::ostringstream oss;
		oss << "cannot bind socket (address: " << _address << ')';
		throw std::runtime_error(oss.str());
	}
	if (::listen(_fd, SOMAXCONN) < 0)
	{
		std::ostringstream oss;
		oss << "Cannot listen on socket (address: " << _address << ')';
		throw std::runtime_error(oss.str());
	}
#ifdef DEBUG
	std::cerr << "Listening on " << _address << std::endl;
#endif
}

// Examples for address : "90,.12.110.57", "127.0.0.1", etc.
/*ServerSocket::ServerSocket(char *address, short port) { //:	_port(port)  {
	_address = INetAddress(INADDR_ANY, port);
	if ((_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::ostringstream oss;
		oss << "Cannot initialize socket (address " << _address << ')';
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
}*/

ServerSocket::~ServerSocket() {
	close(_fd);
}

void	ServerSocket::listen() {
	if (::listen(_fd, SOMAXCONN) < 0)
	{
		std::ostringstream oss;
		oss << "Cannot listen on " << _address;
		throw std::runtime_error(oss.str());
	}
}

ServerSocket*	 ServerSocket::accept() const throw (std::runtime_error)
{
	struct sockaddr_storage		address;
	socklen_t					addr_len;

	addr_len = sizeof(address);
	int newfd = ::accept(_fd, reinterpret_cast<struct sockaddr*>(&address), &addr_len);
	if (newfd < 0)
		throw std::runtime_error("accept: error");
	ServerSocket *newSocket = new ServerSocket();
	newSocket->_fd = newfd;
	newSocket->_address.setPort((*reinterpret_cast<struct sockaddr_in*>(&address)).sin_port);
#ifdef DEBUG 
	std::cerr << "New active socket on: " << newSocket->_address << std::endl;
#endif
	return (newSocket);
}

ssize_t ServerSocket::send(const std::string& message, int flags) throw (std::runtime_error)
{
	return ::send(_fd, message.c_str(), message.length(), flags);
}

ssize_t ServerSocket::send(const void *msg, int len, int flags) throw (std::runtime_error)
{
	ssize_t ret = ::send(_fd, msg, len, flags);
	if (ret < 0)
		throw std::runtime_error("send: error");
	return ret;
}

std::string ServerSocket::recv(int maxlen, int flags) throw (std::runtime_error)
{
	char	tmp[maxlen];
	ssize_t ret = recv(tmp, maxlen, flags);
	return (std::string(tmp, ret));
}

ssize_t ServerSocket::recv(void *buf, int maxlen, int flags) throw (std::runtime_error)
{
	ssize_t ret = ::recv(_fd, buf, maxlen, flags);
	if (ret < 0)
		throw std::runtime_error("recv: error");
	if (ret == 0)
		throw std::runtime_error("recv: remote host closed connection");
	return (ret);
}

int ServerSocket::getFd() const {
	return _fd;
}
