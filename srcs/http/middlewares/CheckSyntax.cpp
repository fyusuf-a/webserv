#include "Middlewares.hpp"

void		CheckSyntax::body(Request & request, Response & response) {
	(void)response;
	std::string met = request.get_method();

	if (met != "GET" && met != "POST" && met != "DELETE")
		throw(501);
	if (request.get_path()[0] != '/')
		throw(400);
	if (request.get_protocol() != "HTTP/1.1")
		throw(505);

	std::map<std::string, std::string>::iterator	it;
	std::string										whitespaces = " \n\r\v\t\f";
	int												host = 0;
	for (it = request.get_header().begin(); it != request.get_header().end(); ++it){
		if (whitespaces.find_first_of(it->first[0]) != std::string::npos)
			throw(400);
		if (whitespaces.find_first_of(it->first[it->first.length()]) != std::string::npos)
			throw(400);
		if (it->first.find("\r\n") != std::string::npos)
			throw(400);
		if (it->first == "Host")
			++host;
	}
	if (host != 1)
		throw (400);

}
