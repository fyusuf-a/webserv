#include "ParsedRequest.hpp"

int	main(void) {
	ParsedRequest test;
	char *str = "GET           /test.html\r\noui: ok\r\nsi: non\r\n\r\nretest: ah\r\n";

	while (*str) {
		str = test.parse(str);
	}
	std::cout << test.get_method() << std::endl;
	std::cout << test.get_path() << std::endl;
	std::cout << test.get_protocol() << std::endl;
	std::cout << test.get_header()["oui"] << std::endl;
	std::cout << test.get_header()["si"] << std::endl;
	std::cout << test.get_body()["retest"] << std::endl;
}