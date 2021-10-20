#ifndef PASSIVESOCKET_HPP
#define PASSIVESOCKET_HPP

#include "INetAddress.hpp"
#include "Socket.hpp"
#include "ActiveServer.hpp"
#include "NIOSelector.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <stdexcept>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <stdexcept>

template<typename T>
class PassiveHTTP : public NIOSelector::Callback {

public:
	PassiveHTTP();
	PassiveHTTP(const PassiveHTTP&);
	PassiveHTTP&	operator=(const PassiveHTTP&);
	PassiveHTTP(const INetAddress& address, bool nonblocking=true);
	PassiveHTTP(uint32_t ip, uint16_t port, bool nonblocking=true);
	virtual 		~PassiveHTTP();

protected:
	Socket			*_socket;
	void			writable(int fd);
	void			readable(int fd);
	void			on_close(int fd);

private:
	void init(const INetAddress& address, bool nonblocking);
};

#include "../templates/PassiveHTTP.tpp"

#endif
