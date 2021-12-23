#include "Middleware.hpp"
#include <sstream>
#include <stdio.h>
#include <string>


//405

void		Error::body(ActiveHTTP&, Request& request, Response& response, MiddlewareChain& next) {


		if (request.get_method() == "HEAD")
			response.set_code(Response::MethodNotAllowed);
		else if (request.get_method() == "PUT")
			response.set_code(Response::OK);

    int code = response.get_code();


	if (code >= 400)
    {
        std::string reason_phrase =
			Response::http_code_to_str(static_cast<Response::http_code>(code));
		std::ostringstream oss;
        
		oss << "<html>\n<head><title>"
			<< code << " " << reason_phrase
			<< "</title></head>\n<body><center><h1>"
			<< code << " " << reason_phrase
        	<< "</h1></center>\n<hr><center>"
			<< SERVER_NAME << "</center>\n</body>\n</html>\n";
        response.set_body(oss.str());
    }
    next();
}
