#include "Middlewares.hpp"
#include <list>

int	main(void) {
	char *str = "GET           /test.html HTTP/1.1\r\nDate: ok\r\nContent-Length: non\r\n\r\nretest: ah\r\n";
	Request test;
	std::list<IMiddlewares *> middlewares;
	std::list<IMiddlewares *>::iterator it;
	CheckSyntax	csx;
	while (test.get_head() != 4) {
		str = test.parse(str);
	}
	middlewares.push_back(&csx);
	try {
		for (it = middlewares.begin(); it != middlewares.end(); ++it){
			(*it)->body(test);
		}
	}
	catch (int code) {test.set_code(code);}
	std::cout << test.get_code() << std::endl;
}