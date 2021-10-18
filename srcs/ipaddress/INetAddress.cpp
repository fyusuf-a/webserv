#include "INetAddress.hpp"
#include <exception>
#include <netinet/in.h>
#include <ostream>
#include <sys/socket.h>

INetAddress::INetAddress() {
	_address.sin_family = AF_INET;
	_address.sin_port = 0;
	_address.sin_addr.s_addr = 0;
	memset(_address.sin_zero, 0, sizeof _address.sin_zero);
}

INetAddress::INetAddress(const INetAddress& src) {
	*this = src;
}

INetAddress::INetAddress(uint32_t address, unsigned short int port) {
	_address.sin_family = AF_INET;
	_address.sin_port = htons(port);
	_address.sin_addr.s_addr = htonl(address);
	memset(_address.sin_zero, 0, sizeof _address.sin_zero);
}

INetAddress& INetAddress::operator=(const INetAddress& src) {
	if (this != &src) {
		_address = src._address;
	}
	return (*this);
}

INetAddress::~INetAddress() {
}

struct sockaddr_in const& INetAddress::getAddress() const {
	return _address;
}

uint32_t INetAddress::getPort() const {
	return _address.sin_port;
}

void INetAddress::setAddress(struct sockaddr_in &addr) {
	_address = addr;
}

void INetAddress::setPort(uint16_t port) {
	_address.sin_port = port;
}

std::ostream& operator<<(std::ostream& os, const INetAddress& addr) {
	struct sockaddr_in	my_addr = addr.getAddress();
	uint32_t			ip = my_addr.sin_addr.s_addr;

	for (int i = 0; i < 4; i++)
	{
		os << ip % 0x100;
		ip /= 0x100;
		if (i != 3)
			os << '.';
	}
	os << ':' << ntohs(my_addr.sin_port);
	return os;
}
