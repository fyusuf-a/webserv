#define DEBUG
#include "TCPServer.hpp"
#include <cctype>

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
				std::cerr << "Connection closed with" << std::endl;
				delete active_socket;
				break;
			}
		}
	}
	return (0);
}
