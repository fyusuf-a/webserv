#include "IPAddress.hpp"
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
}
	

IPAddress& IPAddress::operator=(const IPAddress& src) {
	if (this != &src) {
		_address = src._address;
	}
	return (*this);
}

IPAddress::~IPAddress() {
}

uint32_t IPAddress::getIP() const {
	return _address;
}

void IPAddress::setIP(uint32_t addr) {
	_address = addr;
}

static void print_ip(std::ostream& os, uint32_t ip, int again) {
	if (again == 0)
		return ;
	print_ip(os, ip / 0x100, again - 1);
	os << ip % 0x100 << (again < 4 ? "." : "");
}

bool IPAddress::operator==(const IPAddress& other) {
	return _address == other._address;
}

std::ostream& operator<<(std::ostream& os, const IPAddress& addr) {
	uint32_t ip = addr.getIP();
	print_ip(os, ip, 4);
	return os;
}
