#include "Middleware.hpp"
#include <sstream>
#include <stdio.h>
#include <string>

//405

void		Error::body(ActiveHTTP&, Request&, Response& response, MiddlewareChain& next) {

    int code = response.get_code();

	if (code >= 400)
    {
        std::string reason_phrase =
			Response::http_code_to_str(static_cast<Response::http_code>(code));
		std::ostringstream oss;
        
		oss << "<html>\n<head><title>"
			<< reason_phrase
			<< " Not Found</title></head>\n<body><center><h1>"
			<< reason_phrase
        	<< "</h1></center>\n<hr><center>webserv/1.0.1</center>\n</body>\n</html>\n";
        response.set_body(oss.str());
    }
    next();
}
