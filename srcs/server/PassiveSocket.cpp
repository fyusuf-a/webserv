#include "../../includes/PassiveSocket.hpp"
#include "../../includes/INetAddress.hpp"
#include <cstring>
#include <stdexcept>

PassiveSocket::PassiveSocket() : Socket() {
}

PassiveSocket::PassiveSocket(const PassiveSocket& src) : Socket(src), Callback(src) {
	*this = src;
}

PassiveSocket& PassiveSocket::operator=(const PassiveSocket& src) {
	Socket::operator=(src);
	return *this;
}

PassiveSocket::PassiveSocket(short port, bool nonblocking) : Socket(port, nonblocking) {
	if (::listen(_fd, SOMAXCONN) < 0)
	{
		std::ostringstream oss;
		oss << "Cannot listen on socket (address: " << _address << ')';
		throw std::runtime_error(oss.str() + strerror(errno));
	}
#ifdef DEBUG
	std::cerr << "Listening on " << _address << std::endl;
#endif
}

PassiveSocket::~PassiveSocket() {
}

void	PassiveSocket::listen() {
	if (::listen(_fd, SOMAXCONN) < 0)
	{
		std::ostringstream oss;
		oss << "Cannot listen on " << _address;
		throw std::runtime_error(oss.str());
	}
}

ActiveSocket*	 PassiveSocket::accept()
{
	struct sockaddr_storage		address;
	socklen_t					addr_len;

	addr_len = sizeof(address);
	int newfd = ::accept(_fd, reinterpret_cast<struct sockaddr*>(&address), &addr_len);
	if (newfd < 0)
	{
		throw std::runtime_error(std::string("accept: error") 
				+ strerror(errno));
	}
	ActiveSocket *newSocket = new ActiveSocket();
	newSocket->setFd(newfd);
	newSocket->setPort((*reinterpret_cast<struct sockaddr_in*>(&address)).sin_port);
#ifdef DEBUG 
	std::cerr << "New active socket on: " << newSocket->getAddress() << std::endl;
#endif
	return (newSocket);
}

void			PassiveSocket::readable(int fd) {
	(void)fd;
	ActiveSocket* newSock = accept();
	NIOSelector::getInstance()->add(newSock->getFd(), *newSock, READ | WRITE);
}

void			PassiveSocket::writable(int fd) {
	(void)fd;
}

void			PassiveSocket::on_close(int fd) {
	(void)fd;
}
