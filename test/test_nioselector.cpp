#include "../srcs/server/Socket.hpp"
#include "../srcs/server/ActiveServer.hpp"
#include "../srcs/server/PassiveServer.hpp"
#include "../srcs/server/NIOSelector.hpp"
#include <cctype>
#include <arpa/inet.h>

#define PORT1 8080
#define PORT2 8081
#define MAX_LENGTH 1000

// The following server applies function F to its input and sends it back
template<int (*F)(int)>
class mapCharServer : public ActiveServer {

	public:
	mapCharServer(Socket* socket) : ActiveServer(socket) {
	}

	bool on_readable(int fd) {
		if (ActiveServer::on_readable(fd) == false)
			return (false);
		size_t write_len = _write_buffer.length();
		size_t read_len = _read_buffer.length();
		_write_buffer += _read_buffer;
		for (size_t i = write_len; i < write_len + read_len; i++)
			_write_buffer[i] = F(_write_buffer[i]);
		_read_buffer = "";
		return true;
	}
	/*bool on_writable(int fd) {
		ActiveServer::on_writable(fd);
		return true;
	};
	bool on_close(int fd) {
		ActiveServer::on_close(fd);
		return false;
	}
	bool always(int) {
		return true;
	};*/
};

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	NIOSelector& nio_selector = NIOSelector::getInstance();
	PassiveServer<mapCharServer<toupper> > upper_server(0, PORT1, true);
	PassiveServer<mapCharServer<tolower> > lower_server(0, PORT2, true);

	while (1)
		nio_selector.poll();
	return (0);
}
