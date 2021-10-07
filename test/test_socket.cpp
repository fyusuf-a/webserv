#include "../includes/Socket.hpp"
#include "../includes/ActiveSocket.hpp"
#include "../includes/PassiveSocket.hpp"
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
