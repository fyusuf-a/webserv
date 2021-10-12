#include "../../includes/Socket.hpp"
#include "../../includes/INetAddress.hpp"
#include <stdexcept>

Socket::Socket() {
}

Socket::Socket(const Socket& src) {
	*this = src;
}

Socket& Socket::operator=(const Socket& src) {
	if (this != &src) {
		_fd = src._fd;
		_address = src._address;
	}
	return (*this);
}

Socket::Socket(short port, bool nonblocking) { //:	_port(port)  {
	_address = INetAddress(INADDR_ANY, port);
	if ((_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::ostringstream oss;
		oss << "Cannot initialize socket (address " << _address << ')';
		throw std::runtime_error(oss.str());
	}
	int yes = 1;
#if DEBUG
	std::cerr << "Initialized socket (address " << _address << ')' << std::endl;
#endif
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) < 0)
	{
		std::ostringstream oss;
		oss << "setsockopt: unexpected error while setting socket options (address: " << _address << ')';
		throw std::runtime_error(oss.str());
	}
#if DEBUG
	std::cerr << "Options set (address " << _address << ')' << std::endl;
#endif
	if (nonblocking)
	{
		if (fcntl(_fd, F_SETFL, O_NONBLOCK) < 0)
		{
			std::ostringstream oss;
			oss << "cannot set socket to be not blocking (address: " << _address << ')';
			throw std::runtime_error(oss.str());
		}
	}
#if DEBUG
	std::cerr << "Socket set as nonblocking (address " << _address << ')' << std::endl;
#endif
	struct sockaddr_in my_struct = _address.getAddress();
	if (bind(_fd, (struct sockaddr*)&my_struct, sizeof my_struct) < 0)
	{
		std::cerr << "fd=" << _fd << " address=" << std::endl;
		std::ostringstream oss;
		oss << "cannot bind socket (address: " << _address << strerror(errno) << ')';
		throw std::runtime_error(oss.str());
	}
#if DEBUG
	std::cerr << "Socket bound (address " << _address << ')' << std::endl;
#endif
}

Socket::~Socket() {
	close(_fd);
}

void	Socket::listen() {
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

Socket*	 Socket::accept() const //throw (std::runtime_error)
{
	struct sockaddr_storage		address;
	socklen_t					addr_len;

	addr_len = sizeof(address);
	int newfd = ::accept(_fd, reinterpret_cast<struct sockaddr*>(&address), &addr_len);
	if (newfd < 0)
		throw std::runtime_error("accept: error");
	Socket *newSocket = new Socket();
	newSocket->_fd = newfd;
	newSocket->_address.setPort((*reinterpret_cast<struct sockaddr_in*>(&address)).sin_port);
#ifdef DEBUG 
	std::cerr << "New active socket on: " << newSocket->_address << std::endl;
#endif
	return (newSocket);
}

ssize_t Socket::send(const std::string& message, int flags)
{
	return send(message.c_str(), message.length(), flags);
}

ssize_t Socket::send(const void *msg, int len, int flags)
{
	ssize_t ret = ::send(_fd, msg, len, flags);
	if (ret < 0)
		throw std::runtime_error("send: error");
	return ret;
}

std::string Socket::recv(int maxlen, int flags)
{
	char	tmp[maxlen];
	ssize_t ret = recv(tmp, maxlen, flags);
	return (std::string(tmp, ret));
}

ssize_t Socket::recv(void *buf, int maxlen, int flags)
{
	ssize_t ret = ::recv(_fd, buf, maxlen, flags);
	if (ret < 0)
		throw std::runtime_error("recv: error");
	if (ret == 0)
		throw ConnectionClosed();
	return (ret);
}

int Socket::getFd() const {
	return _fd;
}

INetAddress Socket::getAddress() const {
	return _address;
}

void Socket::setAddress(const INetAddress& addr) {
	_address = addr;
}

void Socket::setFd(const int& fd) {
	_fd = fd;
}

void Socket::setPort(uint16_t port) {
	_address.setPort(port);
}
