#include "../includes/Socket.hpp"
#include "../includes/ActiveSocket.hpp"
#include "../includes/PassiveSocket.hpp"
#include "../includes/NIOSelector.hpp"
#include <cctype>
#include <arpa/inet.h>

#define PORT1 8080
#define PORT2 8081
#define MAX_LENGTH 1000

class toUppercaseActive : public ActiveSocket {
	void readable(int fd) {
		ActiveSocket::readable(fd);
		size_t read_len = _read_buffer.length();
		for (int i = 0; i < read_len; i++)
			_write_buffer += toupper(_read_buffer[i]);
		_read_buffer.substr(0, read_len); 
	}
};

class toUppercasePassive : public PassiveSocket {
	ActiveSocket*	accept() {
		struct sockaddr_storage		address;
		socklen_t					addr_len;

		addr_len = sizeof(address);
		int newfd = ::accept(_fd, reinterpret_cast<struct sockaddr*>(&address), &addr_len);
		if (newfd < 0)
		{
			throw std::runtime_error(std::string("accept: error") 
					+ strerror(errno));
		}
		toUppercaseActive *newSocket = new toUppercaseActive();
		newSocket->setFd(newfd);
		newSocket->setPort((*reinterpret_cast<struct sockaddr_in*>(&address)).sin_port);
#ifdef DEBUG 
		std::cerr << "New active socket on: " << newSocket->getAddress() << std::endl;
#endif
		return (newSocket);
	}
};

int main(int argc, char** argv)
{
	NIOSelector my_selector(100);
	PassiveSocket my_server(atoi(argv[1]), false);

	std::string	received;
	ActiveSocket	*client_socket;
	client_socket = my_server.accept();
	while (1)
	{
		try
		{
			received = client_socket->recv(MAX_LENGTH);
			for (unsigned int i = 0; i < received.length(); i++)
				std::cout << (char)toupper(received[i]);
		}
		catch (std::runtime_error& e)
		{
#ifdef DEBUG
			std::cerr << "Connection closed with " << client_socket->getAddress() << std::endl;
#endif
			delete client_socket;
			break;
		}
	}
	return (0);
}
