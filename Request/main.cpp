#include "Request.hpp"

int	main(void) {
	char *str = "GET           /test.html HTTP/1.1\r\nDate: ok\r\nContent-Length: non\r\n\r\nretest: ah\r\n";
	Request test;

	while (test.get_head() != 4) {
		str = test.parse(str);
	}
	std::cout << test.get_method() << std::endl;
	std::cout << test.get_path() << std::endl;
	std::cout << test.get_protocol() << std::endl;
	std::cout << test.get_header()["Date"] << std::endl;
	std::cout << test.get_header()["Content-Length"] << std::endl;
	std::cout << test.get_body() << std::endl;
}