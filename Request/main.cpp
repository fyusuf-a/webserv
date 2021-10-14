#include "Request.hpp"
#include <list>

void	request_parsing_testing(char *str, bool nouveau, std::list<Request *> & requests, bool clean) {
	std::cout << "---------------------------" << std::endl;
	while (*str) {
		std::cout << str << "/////" <<std::endl;
		if (nouveau)
			requests.push_back(new Request);
		else
			requests.back()->set_over(true);
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
		std::cout << "IS_OVER: " << (*it)->get_over() << std::endl;
		if (!(*it)->get_over()) {
			std::cout << "HEAD: " << (*it)->get_head() << std::endl;			
			std::cout << "RESIDUAL: " << (*it)->get_residual() << std::endl;
		}
	}
	for (it = requests.begin(); it != requests.end(); ++it) {
		if (clean)
			requests.erase(it);
	}
}


int	main(void) {
	std::list<Request *> requests;

	request_parsing_testing("GET           /test.html HTTP/1.1\r\nHost: ok\r\nContent-Length: non\r\n\r\nretest: ah\r\n\r\n", true, requests, true);
	request_parsing_testing("GET           /test.html HTTP/1.1\r\nDate: ok\r\nContent-Length: non\r\n\r\nretest: ah\r\n\r\n", true, requests, true);
	request_parsing_testing("GET           test.html HTTP/1.1\r\nHost: ok\r\nContent-Length: non\r\n\r\nretest: ah\r\n\r\n", true, requests, true);
	request_parsing_testing("GET           /test.html HTTP/1.1\r\nHost: ok\r\nContent-Length: non\r\n\r\nretest: ah\r\n", true, requests, false);
	request_parsing_testing("\r\n", false, requests, true);
	request_parsing_testing("GET  n\r\nretest: ah\r\n\r\n", true, requests, true);
	request_parsing_testing("GT           /t HTP/1.1\r\nHost: ok\r\nContent-Length: non\r\n\r\nretest: ah\r\n\r\n", true, requests, true);
	request_parsing_testing("GET           /t HTP/1.1\r\nHost: ok\r\nContent-Length: non\r\n\r\nretest: ah\r\n\r\n", true, requests, true);
	request_parsing_testing("", true, requests, true);
	request_parsing_testing("GE", true, requests, false);
	request_parsing_testing("T /he", false, requests, false);
	request_parsing_testing("p.com HTTP/1.1\r", false, requests, false);
	request_parsing_testing("\nHost:ok", false, requests, false);
	request_parsing_testing("\r\n\r\n", false, requests, false);
	request_parsing_testing("GET           /test.html HTTP/1.1\r\nHost: ok\r\nContent-Length: non\r\n\r\n", true, requests, false);

}