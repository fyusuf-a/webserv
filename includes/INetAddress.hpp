#ifndef INETADDRESS_HPP
#define INETADDRESS_HPP

#include <cstdio>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <iostream>
#include <arpa/inet.h>

class INetAddress {

    private:
		struct sockaddr_in _address;

    public:
        INetAddress();
		INetAddress(uint32_t address, unsigned short int port);
		INetAddress(const INetAddress&);
		INetAddress& operator=(const INetAddress&);
        virtual ~INetAddress();
		struct sockaddr_in const& getAddress() const;
		uint32_t getPort() const;
		void setAddress(struct sockaddr_in&);
		void setPort(uint16_t);
};

std::ostream& operator<<(std::ostream&, const INetAddress&);

#endif
