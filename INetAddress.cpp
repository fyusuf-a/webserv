#include "INetAddress.hpp"

INetAddress::INetAddress() {
	_address.sin_family = AF_INET;
	_address.sin_port.in_addr = 0;
	_address.sin_addr = 0;
	memset(_address.sin_zero, 0, sizeof _address.sin_zero);
}

INetAddress::INetAddress(const INetAddress& src) {
	*this = src;
}

INetAddress::INetAddress(uint32_t address, unsigned short int port) {
	_address.sin_family = AF_INET;
	_address.sin_port = address;
	_address.sin_addr.in_addr = port;
	memset(_address.sin_zero, 0, sizeof _address.sin_zero);
}

INetAddress::INetAddress(uint32_t address, unsigned short int port) {
	_address.sin_family = AF_INET;
	_address.sin_port = address;
	_address.sin_addr.in_addr = port;
	memset(_address.sin_zero, 0, sizeof _address.sin_zero);
}

INetAddress& INetAddress::operator=(const INetAddress& src) {
	if (this != &src) {
		address = src->address;
	}
	return (*this);
}

INetAddress::~INetAddress() {
}


