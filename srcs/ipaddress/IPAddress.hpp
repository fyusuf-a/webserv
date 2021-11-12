#ifndef IPADDRESS_HPP
#define IPADDRESS_HPP

#include <cstdio>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <iostream>
#include <arpa/inet.h>

class IPAddress {

    private:
		uint32_t _address;

    public:
        IPAddress();
		IPAddress(const std::string& str);
		IPAddress(uint32_t address);
		IPAddress(const IPAddress&);
		IPAddress& operator=(const IPAddress&);
        virtual ~IPAddress();
		uint32_t getIP() const;
		void setIP(uint32_t);
		bool operator==(const IPAddress&);
};

bool operator==(const IPAddress& lhs, const IPAddress& rhs);

std::ostream& operator<<(std::ostream&, const IPAddress&);

#endif
