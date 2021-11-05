#include "INetAddress.hpp"
#include <exception>
#include <ostream>
#include <sys/socket.h>

INetAddress::INetAddress() : _address(0), _port(0) {
}

INetAddress::INetAddress(const INetAddress& src) {
	*this = src;
}

INetAddress::INetAddress(const IPAddress& address, uint16_t port) : _address(address), _port(port) {
}

INetAddress& INetAddress::operator=(const INetAddress& src) {
	if (this != &src) {
		_address = src._address;
		_port = src._port;
	}
	return (*this);
}

INetAddress::~INetAddress() {
}

IPAddress const& INetAddress::getAddress() const {
	return _address;
}

uint16_t INetAddress::getPort() const {
	return _port;
}

void INetAddress::setAddress(IPAddress &addr) {
	_address = addr;
}

void INetAddress::setPort(uint16_t port) {
	_port = port;
}

void INetAddress::to_sockaddr_in(struct sockaddr_in* structure) {
	if (!structure)
		return;
	structure->sin_family = AF_INET;
	structure->sin_port = htons(_port);
	structure->sin_addr.s_addr = htonl(_address.getIP());
	memset(structure->sin_zero, 0, sizeof(structure->sin_zero));
}

std::ostream& operator<<(std::ostream& os, const INetAddress& addr) {
	os << addr.getAddress() << ":" << addr.getPort();
	return os;
}
