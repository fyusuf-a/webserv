#include "includes/NIOSelector.hpp"
#include "includes/TCPServer.hpp"

class CapitalizeServer : public Callback {
	public:


	private:



}

int main() {
	TCPServer capitalize_server(80);
	TCPServer prepend_lol_server(443);

	int	fd1 = capitalize_server.getFd();
	int	fd2 = prepend_lol_server.getFd();



}
