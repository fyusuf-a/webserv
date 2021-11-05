#include "middlewares/Middlewares.hpp"
#include <list>

/*void	req_check_syntax(char *str) {

	Request		req;
	Response 	resp;
	std::list<IMiddlewares *> middlewares;
	std::list<IMiddlewares *>::iterator it;
	std::map<std::string, std::string>::iterator it2;
	CheckSyntax	csx;

	std::cout << "------------------------" << std::endl;
	std::cout << "Requete :" << std::endl;
	std::cout << str << std::endl;
	std::cout << "------------------------" << std::endl;

	while (req.get_head() < 6 && req.get_over() == true)
		str = req.parse(str);

	std::cout << "method: " << req.get_method() << std::endl;
	std::cout << "path: " << req.get_path() << std::endl;
	std::cout << "protocol: " << req.get_protocol() << std::endl;
	std::cout << "///HEADERS" << std::endl;
	for (it2 = (*req.get_header()).begin(); it2 != (*req.get_header()).end(); ++it2)
		std::cout << it2->first << ": " << it2->second << std::endl;
	std::cout << "///" << std::endl;
	std::cout << "body: " << req.get_body() << std::endl;
	std::cout << "head: " << req.get_head() << std::endl;
	std::cout << "over: " << req.get_over() << std::endl;
	middlewares.push_back(&csx);
	try {
		for (it = middlewares.begin(); it != middlewares.end(); ++it) {
			(*it)->body(req, resp);
		}
	}
	catch (int code) {resp.set_code(code);}
	std::cout << resp.get_code() << std::endl;
}

void	check_sntx(void) {
	req_check_syntax((char *)"GET           /req.html HTTP/1.1\r\nHost: ok\r\nContent-Length: non\r\n\r\nrereq: ah\r\n\r\n");
	req_check_syntax((char *)"GET           /req.html HTTP/1.1\r\nDate: ok\r\nContent-Length: non\r\n\r\nrereq: ah\r\n\r\n");
	req_check_syntax((char *)"GET           req.html HTTP/1.1\r\nHost: ok\r\nContent-Length: non\r\n\r\nrereq: ah\r\n\r\n");
	req_check_syntax((char *)"GET           /req.html HTTP/1.1\r\nHost: ok\r\nContent-Length: non\r\n\r\nrereq: ah\r\n");

	req_check_syntax((char *)"GET  n\r\nrereq: ah\r\n\r\n");
	req_check_syntax((char *)"GT           /t HTP/1.1\r\nHost: ok\r\nContent-Length: non\r\n\r\nrereq: ah\r\n\r\n");
	req_check_syntax((char *)"GET           /t HTP/1.1\r\nHost: ok\r\nContent-Length: non\r\n\r\nrereq: ah\r\n\r\n");
	req_check_syntax((char *)"GET           /t HTreq: ah\r\n\r\n");
	req_check_syntax((char *)"GEnHost: ok\r\nContent-Length: non\r\n\r\nrereq: ah\r\n\r\n");
	req_check_syntax((char *)"GETr\nHost: ok\r\r\nrereq: ah\r\n\r\n");
	req_check_syntax((char *)"GET           /t HTP/1.1\r\nHost: ok\r\nContent-Lengthrereq ah\r\n\r\n");
	req_check_syntax((char *)"");

}*/


//request_parsing_testing((char *)"GET           /test.html HTTP/1.1\r\nHost: ok\r\nContent-Length: non\r\n\r\nretest: ah\r\n\r\n", true, requests, true);
/*Request try_parse(std::string& str) {
	Request req;

	bool nouveau = true;
	while (*cstr) {
		if (!nouveau)
			req.set_over(true);
		while (req.get_head() < 6 && req.get_over() == true)
			cstr = req.parse(cstr);
		nouveau = req.get_over();
	}
	std::cout << req << std::endl;
}*/

void	request_parsing_testing(const char* str, bool nouveau, std::list<Request *> & requests, bool clean) {
	while (*str) {
		if (nouveau)
			requests.push_back(new Request);
		else
			requests.back()->set_over(true);
		while (requests.back()->get_head() < 6 && requests.back()->get_over() == true)
		{
			str = requests.back()->parse(str);
		}
		nouveau = requests.back()->get_over();
	}

	std::list<Request *>::iterator it;
	std::map<std::string, std::string>::iterator it2;

	std::cout << *requests.back();

	if (clean) {
		for (it = requests.begin(); it != requests.end(); ++it)
			delete *it;
		requests.clear();
	}
	else {
		try {requests.back()->checkIncompleteRequest();}
		catch (int error) { std::cout << error << std::endl; }
	}
}


void	rpt(void) {
	std::list<Request *> requests;

	Request req;
	//try_parse((char *)"GET           /test.html HTTP/1.1\r\nHost: ok\r\nContent-Length: non\r\nok: ok\r\nretest: ah\r\nuseless: useless\r\n\r\n", req);
	std::string lol("GET           /test.html HTTP/1.1\r\nHost: ok\r\nContent-Length: non\r\nok: ok\r\nretest: ah\r\nuseless: useless\r\n\r\n");
	request_parsing_testing(lol.c_str(), true, requests, true);
	//request_parsing_testing((char *)"GET           /test.html HTTP/1.1\r\nDate: ok\r\nContent-Length: non\r\n\r\nretest: ah\r\n\r\n", true, requests, true);
	//request_parsing_testing((char *)"GET           test.html HTTP/1.1\r\nHost: ok\r\nContent-Length: non\r\n\r\nretest: ah\r\n\r\n", true, requests, true);
	//request_parsing_testing((char *)"GET           /test.html HTTP/1.1\r\nHost: ok\r\nContent-Length: non\r\n\r\nretest: ah\r\n", true, requests, false);
	//request_parsing_testing((char *)"\r\n", false, requests, true);
	//request_parsing_testing((char *)"GET  n\r\nretest: ah\r\n\r\n", true, requests, true);
	//request_parsing_testing((char *)"GT           /t HTP/1.1\r\nHost: ok\r\nContent-Length: non\r\n\r\nretest: ah\r\n\r\n", true, requests, true);
	//request_parsing_testing((char *)"GET           /t HTP/1.1\r\nHost: ok\r\nContent-Length: non\r\n\r\nretest: ah\r\n\r\n", true, requests, true);
//void	request_parsing_testing(char *str, bool nouveau, std::list<Request *> & requests, bool clean) {
	//request_parsing_testing((char *)"", true, requests, true);
	//request_parsing_testing((char *)"G", true, requests, false);
	//request_parsing_testing((char *)"ET", false, requests, false);
	//request_parsing_testing((char *)" /", false, requests, false);
	//request_parsing_testing((char *)"p.comHTTP/1.1", false, requests, false);
	//request_parsing_testing((char *)"nHost:ok", false, requests, false);
	//request_parsing_testing((char *)"\r\n\r\n", false, requests, true);
	//request_parsing_testing((char *)"G", true, requests, false);
	//request_parsing_testing((char *)"ET ", false, requests, false);
	//request_parsing_testing((char *)" l/", false, requests, false);
	//request_parsing_testing((char *)"p.com HTTP/1.", false, requests, false);
	//request_parsing_testing((char *)"1\r\nHost:ok", false, requests, false);
	//request_parsing_testing((char *)"\r\n\r\n", false, requests, true);
	//request_parsing_testing((char *)"GET           /test.html HTTP/1.1\r\nHost: \r\nContent-Length: non\r\n \r\n\r\n", true, requests, true);
	//request_parsing_testing((char *)"GET /lp HTT.1", true, requests, false);

}

int	main(void) {
	rpt();
	//check_sntx();

}
