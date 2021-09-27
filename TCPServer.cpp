#include "TCPServer.hpp"
#include <sys/socket.h>

TCPServer::TCPServer() {

}

TCPServer::TCPServer(int fd) {
	struct sockaddr_in address;
	int fd = socket(PF_INET, SOCK_STREAM, 0);

	if (fd < 0)
		return ;
	
	htons(port)

}

TCPServer::TCPServer(const TCPServer& src) : h(src.h) {
}

TCPServer& TCPServer::operator=(const TCPServer& src) {
	if (this != &src)
		h = src.h;
	return (*this);
}

TCPServer::~TCPServer() {
}

