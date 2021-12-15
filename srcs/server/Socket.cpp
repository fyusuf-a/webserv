#include "Socket.hpp"
#include "../ipaddress/INetAddress.hpp"
#include <cstring>
#include <stdexcept>

Log& Socket::LOG = Log::getInstance();

Socket::Socket() : _peer(NULL) {
}

Socket::Socket(const Socket& src) : _peer(NULL) {
	*this = src;
}

Socket& Socket::operator=(const Socket& src) {
	if (this != &src) {
		_fd = src._fd;
		_interface = src._interface;
		if (_peer)
			delete _peer;
		_peer = src._peer ? new INetAddress(*src._peer) : NULL;
	}
	return (*this);
}

void Socket::init(const IPAddress& ip, uint16_t port, bool nonblocking) {
	_interface = INetAddress(ip, port);
	if ((_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::ostringstream oss;
		oss << "Cannot initialize socket (address " << ip << ":" << port << ')';
		throw std::runtime_error(oss.str());
	}
	int yes = 1;
	LOG.debug() << "Initialized socket (address " << _interface << ')' << std::endl;
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) < 0)
	{
		std::ostringstream oss;
		oss << "setsockopt: unexpected error while setting socket options (address: " << _interface << ')';
		throw std::runtime_error(oss.str());
	}
	LOG.debug() << "Options set (address " << _interface << ')' << std::endl;
	if (nonblocking)
	{
		if (fcntl(_fd, F_SETFL, O_NONBLOCK) < 0)
		{
			std::ostringstream oss;
			oss << "cannot set socket to be not blocking (address: " << _interface << ')';
			throw std::runtime_error(oss.str());
		}
		LOG.debug() << "Socket set as nonblocking (address " << _interface << ')' << std::endl;
	}
	struct sockaddr_in my_struct;
	_interface.to_sockaddr_in(&my_struct);
	if (bind(_fd, (struct sockaddr*)&my_struct, sizeof my_struct) < 0)
	{
		std::ostringstream oss;
		if (errno == EACCES)
			LOG.error() << "Access denied on address " << _interface << std::endl;
		else if (errno == EADDRINUSE)
			LOG.debug() << "Address already in use " << _interface << std::endl;
		else if (errno == EADDRNOTAVAIL)
			LOG.error() << "Address " << _interface << " is not available" << std::endl;
		oss << "cannot bind socket (address: " << _interface << ')';
		throw std::runtime_error(oss.str());
	}
	LOG.debug() << "Socket bound (address " << _interface << ')' << std::endl;
}

Socket::Socket(const IPAddress& ip, uint16_t port, bool nonblocking) { //:	_port(port)  {
	init(ip, port, nonblocking);
}

Socket::Socket(const INetAddress& address, bool nonblocking) {
	init(address.getAddress(), address.getPort(), nonblocking);
}

Socket::~Socket() {
	if (_peer)
		delete _peer;
	close(_fd);
}

void	Socket::listen() {
	if (::listen(_fd, SOMAXCONN) < 0)
	{
		std::ostringstream oss;
		oss << "Cannot listen on socket (address: " << _interface << ')';
		throw std::runtime_error(oss.str());
	}
	LOG.info() << "Listening on " << _interface << " (fd " << _fd << ")" << std::endl;
}

Socket*	 Socket::accept() const //throw (std::runtime_error)
{
	struct sockaddr_storage		address;
	socklen_t					addr_len;

	addr_len = sizeof(address);
	int newfd = ::accept(_fd, reinterpret_cast<struct sockaddr*>(&address), &addr_len);
	if (newfd < 0)
	{
		LOG.debug() << "accept failed: " << std::strerror(errno) << std::endl;
		throw std::runtime_error("accept: error");
	}
	Socket *newSocket = new Socket();
	newSocket->_fd = newfd;

	//Setting peer for active socket
	newSocket->_peer = new INetAddress();
	newSocket->_peer->setPort(reinterpret_cast<struct sockaddr_in&>(address).sin_port);
	IPAddress new_addr = ntohl(reinterpret_cast<struct sockaddr_in&>(address).sin_addr.s_addr);
	newSocket->_peer->setAddress(new_addr);

	//Setting interface for active socket
	int ret;
	if ((ret = ::getsockname(newfd, reinterpret_cast<struct sockaddr*>(&address), &addr_len)) >= 0) {
		newSocket->_interface.setPort(reinterpret_cast<struct sockaddr_in&>(address).sin_port);
		IPAddress new_addr = ntohl(reinterpret_cast<struct sockaddr_in&>(address).sin_addr.s_addr);
		newSocket->_interface.setAddress(new_addr);
	}
	else
		LOG.warning() << "getsockname: " << ::strerror(ret) << std::endl;

	LOG.debug() << "New active socket on: " << newSocket->_interface << std::endl;
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

INetAddress const& Socket::getInterface() const {
	return _interface;
}

INetAddress *Socket::getPeer() const {
	return _peer;
}

void Socket::setInterface(const INetAddress& interface) {
	_interface = interface;
}

void Socket::setFd(const int& fd) {
	_fd = fd;
}

void Socket::setPort(uint16_t port) {
	_interface.setPort(port);
}
