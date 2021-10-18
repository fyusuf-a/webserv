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

	my_server.listen();

	ssize_t			received;
	Socket	*client_socket;
	client_socket = my_server.accept();
	while (1)
	{
			char tmp[MAX_LENGTH];
			try {
				received = client_socket->recv(tmp, MAX_LENGTH);
				for (unsigned int i = 0; i < received; i++)
					std::cout << (char)toupper(tmp[i]);
			}
			catch (Socket::ConnectionClosed& e) {
				break;
			}
			catch (std::exception& e) {
				std::cerr << e.what() << std::endl;
				break;
			}
	}
	delete client_socket;
	return (0);
}
