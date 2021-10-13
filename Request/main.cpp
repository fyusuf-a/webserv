#include "Request.hpp"
#include <list>

int	main(void) {
	char *str = "GET           /test.html HTTP/1.1\r\nDate: ok\r\nContent-Length: non\r\n\r\nretest: ah\r\n\r\nGET           /tete.html HTTP/1.1\r\nDate: ok\r\nContent-Length: non\r\n\r\nretest: ah\r\n\r\n";
	std::list<Request *> requests;
	bool	nouveau = true;
	while (*str) {
		if (nouveau)
			requests.push_back(new Request);
		while (requests.back()->get_head() < 4 && requests.back()->get_over() == true)
			str = requests.back()->parse(str);
		nouveau = requests.back()->get_over();
	}

	std::list<Request *>::iterator it;
	std::map<std::string, std::string>::iterator it2;

	for (it = requests.begin(); it != requests.end(); ++it) {
		std::cout << (*it)->get_method() << std::endl;
		std::cout << (*it)->get_path() << std::endl;
		std::cout << (*it)->get_protocol() << std::endl;
		for (it2 = ((*it)->get_header())->begin(); it2 != ((*it)->get_header())->end(); ++it2)
			std::cout << it2->first << ": " << it2->second << std::endl;
		std::cout << (*it)->get_body() << std::endl;
		std::cout << (*it)->get_over() << std::endl;
	}
}