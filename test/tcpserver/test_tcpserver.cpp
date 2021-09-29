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
	TCPServer my_server(atoi(argv[1]));

	std::string	received;
	TCPServer	*active_socket;
	active_socket = my_server.accept();
	while (1)
	{
		try
		{
			received = active_socket->recv(MAX_LENGTH);
			for (unsigned int i = 0; i < received.length(); i++)
				std::cout << (char)toupper(received[i]);
		}
		catch (std::runtime_error& e)
		{
#ifdef DEBUG
			std::cerr << "Connection closed with " << active_socket->_address << std::endl;
#endif
			delete active_socket;
			break;
		}
	}
	return (0);
}
