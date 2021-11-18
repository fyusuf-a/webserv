#include "Middleware.hpp"
#include "MiddlewareChain.hpp"

CheckSyntax::CheckSyntax() {
}

void		CheckSyntax::body(ActiveHTTP& actHTTP, Request & request, Response & response, MiddlewareChain& next) {
	(void)actHTTP;
	
	std::string met = request.get_method();

	if (met != "GET" && met != "POST" && met != "DELETE")
		response.set_code(Response::NotImplemented);
	else if (request.get_path()[0] != '/')
		response.set_code(Response::BadRequest);
	else if (request.get_protocol() != "HTTP/1.1")
		response.set_code(Response::HTTPNotSupported);

    if (response.get_code() >= 400) {
        next();
        return ;
    }

	std::map<std::string, std::string>::const_iterator	it;
	std::string										whitespaces = " \n\r\v\t\f";
	int												host = 0;
		bool set = false;

//----
	for (it = request.get_header().begin(); it != request.get_header().end(); ++it){
		if (it->first == "Host")
			set = true;
	}
	if (set == false)
		request.get_header()["Host"] = "test";
// ----
		

	for (it = request.get_header().begin(); it != request.get_header().end(); ++it){

	    if (response.get_code() >= 400) {
	        next();
	        return ;
	    }
		if (it->first == "Host")
			++host;
		if (whitespaces.find_first_of(it->first[0]) != std::string::npos)
			response.set_code(Response::BadRequest);
		else if (whitespaces.find_first_of(it->first[it->first.length()]) != std::string::npos)
			response.set_code(Response::BadRequest);
	}



	if (response.get_code() < 400 && host != 1)
		response.set_code(Response::BadRequest);
	next();
}
