#ifndef INETADDRESS_HPP
#define INETADDRESS_HPP
#include <cstdio>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <iostream>
#include <arpa/inet.h>
#include "IPAddress.hpp"

class INetAddress {

    private:
		IPAddress _address;
		uint16_t  _port;
		//struct sockaddr_in _address;

    public:
        INetAddress();
		INetAddress(const IPAddress& address, uint16_t port);
		INetAddress(const INetAddress&);
		INetAddress& operator=(const INetAddress&);
        virtual ~INetAddress();
		IPAddress const& getAddress() const;
		uint16_t getPort() const;
		void setAddress(IPAddress&);
		void setPort(uint16_t);
		void to_sockaddr_in(struct sockaddr_in*);
		bool operator==(const INetAddress&);
};

std::ostream& operator<<(std::ostream&, const INetAddress&);

#endif
