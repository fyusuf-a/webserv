#include "../../includes/IPAddress.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <netinet/in.h>

IPAddress::IPAddress() : _address(0) {
}

IPAddress::IPAddress(const IPAddress& src) {
	*this = src;
}

IPAddress::IPAddress(uint32_t address) : _address(address) {
}

IPAddress::IPAddress(const std::string& str) {
	uint64_t byte[4];
	std::stringstream ss;
	ss << str;
	for (int i = 0; i < 4; i++) {
		ss >> byte[i];
		if (byte[i] >= 0xff)
			throw std::invalid_argument("Number is not in range 0-255");
		if (i < 3 && ss.get() != '.')
			throw std::invalid_argument("Invalid IP address");
	}
	if (ss.get() != EOF)
		throw std::invalid_argument("Invalid IP address");
	_address = 0;
	for (int i = 0; i < 4; i++)
		_address = 0x100 * _address + byte[i];
	_address = htonl(_address);
}
	

IPAddress& IPAddress::operator=(const IPAddress& src) {
	if (this != &src) {
		_address = src._address;
	}
	return (*this);
}

IPAddress::~IPAddress() {
}

uint32_t IPAddress::getAddress() const {
	return _address;
}

void IPAddress::setAddress(uint32_t addr) {
	_address = addr;
}

std::ostream& operator<<(std::ostream& os, const IPAddress& addr) {
	uint32_t ip = addr.getAddress();
	for (int i = 0; i < 4; i++)
	{
		os << ip % 0x100;
		ip /= 0x100;
		if (i != 3)
			os << '.';
	}
	return os;
}