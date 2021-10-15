#include "../includes/Socket.hpp"
#include "../includes/ActiveServer.hpp"
#include "../includes/PassiveServer.hpp"
#include "../includes/NIOSelector.hpp"
#include <cctype>
#include <arpa/inet.h>

#define PORT1 8080
#define PORT2 8081
#define MAX_LENGTH 1000

class toUppercaseActive : public ActiveServer {

	public:
	toUppercaseActive(Socket* socket) : ActiveServer(socket) {
	}
	void readable(int fd) {
		ActiveServer::readable(fd);
		size_t write_len = _write_buffer.length();
		size_t read_len = _read_buffer.length();
		_write_buffer += _read_buffer;
		for (size_t i = write_len; i < write_len + read_len; i++)
			_write_buffer[i] = toupper(_write_buffer[i]);
		_read_buffer = "";
	}
};

class toLowercaseActive : public ActiveServer {

	public:
	toLowercaseActive(Socket* socket) : ActiveServer(socket) {
	}
	void readable(int fd) {
		ActiveServer::readable(fd);
		size_t write_len = _write_buffer.length();
		size_t read_len = _read_buffer.length();
		_write_buffer += _read_buffer;
		for (size_t i = write_len; i < write_len + read_len; i++)
			_write_buffer[i] = tolower(_write_buffer[i]);
		_read_buffer = "";
	}
};

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	NIOSelector* nio_selector = NIOSelector::getInstance(100);
	PassiveServer<toUppercaseActive> upper_server(PORT1, false);
	PassiveServer<toLowercaseActive> lower_server(PORT2, false);

	while (1)
		nio_selector->poll();
	return (0);
}
