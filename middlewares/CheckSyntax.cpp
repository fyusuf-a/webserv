#include "Middlewares.hpp"

void		CheckSyntax::body(Request & request) {
	std::string met = request.get_method();

	if (met != "GET" && met != "POST" && met != "DELETE")
		throw(501);
	if (request.get_path()[0] != '/')
		throw(400);
	if (request.get_protocol() != "HTTP/1.1")
		throw(505);

	std::map<std::string, std::string>::iterator it;
	std::string	whitespaces = " \n\r\v\t\f";
	for (it = request.get_header()->begin(); it != request.get_header()->end(); ++it){
		if (whitespaces.find_first_of(it->first.front()) != std::string::npos)
			throw(400);
		if (whitespaces.find_first_of(it->first.back()) != std::string::npos)
			throw(400);
		if (it->first.find("\r\n") != std::string::npos)
			throw(400);
	}


}