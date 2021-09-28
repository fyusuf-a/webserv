#ifndef DEBUG
# define DEBUG
#endif
#include "TCPServer.hpp"
#include <cctype>
#include <arpa/inet.h>

#define MAX_LENGTH 1000

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "No port was given as an argument" << std::endl;
		return 1;
	}
	TCPSocket my_server(atoi(argv[1]));

	std::string	received;
	while (1)
	{
		TCPSocket	*active_socket;
		active_socket = my_server.accept();
		while (1)
		{
			try
			{
				received = active_socket->recv(MAX_LENGTH);
				for (int i = 0; i < received.length(); i++)
					std::cout << (char)toupper(received[i]);
			}
			catch (std::runtime_error& e)
			{
				char str[INET_ADDRSTRLEN];
				std::cerr << "Connection closed with" << inet_ntop(AF_INET, active_socket->_address, str, INET_ADDRSTRLEN) << " " << active_socket->_port << std::endl;
	//inet_pton(AF_INET, address, &(my_addr.sin_addr));
				delete active_socket;
				break;
			}
		}
	}
	return (0);
}
