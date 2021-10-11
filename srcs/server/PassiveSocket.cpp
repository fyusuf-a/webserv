#include "../../includes/PassiveSocket.hpp"
#include "../../includes/INetAddress.hpp"
#include <cstring>
#include <stdexcept>

template<typename T>
PassiveSocket<T>::PassiveSocket() : Socket() {
}

template<typename T>
PassiveSocket<T>::PassiveSocket(const PassiveSocket& src) : Socket(src), Callback(src) {
	*this = src;
}

template<typename T>
PassiveSocket<T>& PassiveSocket<T>::operator=(const PassiveSocket& src) {
	Socket::operator=(src);
	return *this;
}

template<typename T>
PassiveSocket<T>::PassiveSocket(short port, bool nonblocking) : Socket(port, nonblocking) {
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

template<typename T>
PassiveSocket<T>::~PassiveSocket() {
}

template<typename T>
void	PassiveSocket<T>::listen() {
	if (::listen(_fd, SOMAXCONN) < 0)
	{
		std::ostringstream oss;
		oss << "Cannot listen on " << _address;
		throw std::runtime_error(oss.str());
	}
}

template<typename T>
T*	 PassiveSocket<T>::accept()
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
	T *newSocket = new ActiveSocket();
	newSocket->setFd(newfd);
	newSocket->setPort((*reinterpret_cast<struct sockaddr_in*>(&address)).sin_port);
#ifdef DEBUG 
	std::cerr << "New active socket on: " << newSocket->getAddress() << std::endl;
#endif
	return (newSocket);
}

template<typename T>
void			PassiveSocket<T>::readable(int fd) {
	(void)fd;
	ActiveSocket* newSock = accept();
	NIOSelector::getInstance()->add(newSock->getFd(), *newSock, READ | WRITE);
}

template<typename T>
void			PassiveSocket<T>::writable(int fd) {
	(void)fd;
}

template<typename T>
void			PassiveSocket<T>::on_close(int fd) {
	(void)fd;
}
