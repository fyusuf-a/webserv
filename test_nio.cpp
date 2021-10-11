#include "includes/ActiveSocket.hpp"
#include "includes/NIOSelector.hpp"
#include "includes/PassiveSocket.hpp"

#define PORT1 8080
#define PORT2 8081

class CapitalizeServer : public ActiveSocket {
	void readable(int fd) {
		ActiveSocket::readable(fd);
		for (int i = 0; i < _write_buffer.length(); i++);
		_write_buffer.

}

int main() {
	PassiveSocket capitalize_server(PORT1);
	PassiveSocket prepend_lol_server(PORT2);

	int	fd1 = capitalize_server.getFd();
	int	fd2 = prepend_lol_server.getFd();



}
