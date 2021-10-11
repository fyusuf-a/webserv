#include "Middlewares.hpp"
#include <list>

void	test_check_syntax(char *str) {

	Request test;
	std::list<IMiddlewares *> middlewares;
	std::list<IMiddlewares *>::iterator it;
	std::map<std::string, std::string>::iterator it2;
	CheckSyntax	csx;

	std::cout << "------------------------" << std::endl;
	std::cout << "Requete :" << std::endl;
	std::cout << str << std::endl;
	std::cout << "------------------------" << std::endl;

	while (test.get_head() < 4 && test.get_over() == true)
		str = test.parse(str);

	std::cout << "method: " << test.get_method() << std::endl;
	std::cout << "path: " << test.get_path() << std::endl;
	std::cout << "protocol: " << test.get_protocol() << std::endl;
	std::cout << "///HEADERS" << std::endl;
	for (it2 = (*test.get_header()).begin(); it2 != (*test.get_header()).end(); ++it2)
		std::cout << it2->first << ": " << it2->second << std::endl;
	std::cout << "///" << std::endl;
	std::cout << "body: " << test.get_body() << std::endl;
	std::cout << "head: " << test.get_head() << std::endl;
	std::cout << "over: " << test.get_over() << std::endl;
	middlewares.push_back(&csx);
	try {
		for (it = middlewares.begin(); it != middlewares.end(); ++it) {
			(*it)->body(test);
		}
	}
	catch (int code) {test.set_code(code);}
	std::cout << test.get_code() << std::endl;
}

int	main(void) {
	test_check_syntax("GET           /test.html HTTP/1.1\r\nHost: ok\r\nContent-Length: non\r\n\r\nretest: ah\r\n\r\n");
	test_check_syntax("GET           /test.html HTTP/1.1\r\nDate: ok\r\nContent-Length: non\r\n\r\nretest: ah\r\n\r\n");
	test_check_syntax("GET           test.html HTTP/1.1\r\nHost: ok\r\nContent-Length: non\r\n\r\nretest: ah\r\n\r\n");
	test_check_syntax("GET           /test.html HTTP/1.1\r\nHost: ok\r\nContent-Length: non\r\n\r\nretest: ah\r\n");

	test_check_syntax("GET  n\r\nretest: ah\r\n\r\n");
	test_check_syntax("GT           /t HTP/1.1\r\nHost: ok\r\nContent-Length: non\r\n\r\nretest: ah\r\n\r\n");
	test_check_syntax("GET           /t HTP/1.1\r\nHost: ok\r\nContent-Length: non\r\n\r\nretest: ah\r\n\r\n");
	test_check_syntax("");

}