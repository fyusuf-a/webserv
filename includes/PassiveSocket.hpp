#ifndef PASSIVESOCKET_HPP
#define PASSIVESOCKET_HPP

#include "INetAddress.hpp"
#include "ActiveSocket.hpp"
#include "Socket.hpp"
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

template<typename DERIVED_FROM_ACTIVE_SOCKET = ActiveSocket>
class PassiveSocket : public Socket, public NIOSelector::Callback {

public:
	PassiveSocket();
	PassiveSocket(short port, bool nonblocking=true);
	PassiveSocket(const PassiveSocket&);
	PassiveSocket&	operator=(const PassiveSocket&);
	virtual 		~PassiveSocket();
	void			listen();
	virtual DERIVED_FROM_ACTIVE_SOCKET*	accept();

	void			writable(int fd);
	void			readable(int fd);
	void			on_close(int fd);
};

#endif
