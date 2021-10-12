#include "../includes/Socket.hpp"
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
	Socket my_server(atoi(argv[1]), false);

	ssize_t			received;
	Socket	*client_socket;
	client_socket = my_server.accept();
	while (1)
	{
			char tmp[MAX_LENGTH];
			received = client_socket->recv(tmp, MAX_LENGTH);
			if (received > 0)
				for (unsigned int i = 0; i < received; i++)
					std::cout << (char)toupper(tmp[i]);
			if (received == 0)
				break;
	}
	return (0);
}
