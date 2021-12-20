#include "Middleware.hpp"
#include "MiddlewareChain.hpp"

void		CheckSyntax::body(ActiveHTTP& actHTTP, Request & request, Response & response, MiddlewareChain& next) {
	(void)actHTTP;
	
    if (response.get_code() >= 400) {
        next();
        return ;
    }
	std::string met = request.get_method();


	if (request.get_wrong())
		response.set_code(Response::BadRequest);
	else if (request.get_too_big_body())
		response.set_code(Response::RequestEntityTooLarge);	
	else if (met != "GET" && met != "POST" && met != "DELETE")
		response.set_code(Response::NotImplemented);
	else if (request.get_path()[0] != '/')
		response.set_code(Response::BadRequest);
	else if (request.get_protocol() != SERVER_PROTOCOL)
		response.set_code(Response::HTTPNotSupported);

    if (response.get_code() >= 400) {
        next();
        return ;
    }

	std::map<std::string, std::string>::const_iterator	it;
	std::string										whitespaces = " \n\r\v\t\f";
	int												host = 0;

	if (request.get_headers().size() == 0) {
		response.set_code(Response::BadRequest);
		next();
		return ;
	}
		
	for (it = request.get_headers().begin(); it != request.get_headers().end(); ++it){
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
