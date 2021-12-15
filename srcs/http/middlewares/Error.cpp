#include "Middleware.hpp"
#include <sstream>
#include <stdio.h>
#include <string>


//405

void		Error::body(ActiveHTTP&, Request&, Response& response, MiddlewareChain& next) {

    int code = response.get_code();

	if (code >= 400)
    {
        std::string error_body;
        
        error_body =
        "<html>\n<head><title>"
        + Utils::toString(code) +
        " Not Found</title></head>\n<body><center><h1>"
        + Utils::toString(code) +
        " Not Found</h1></center>\n<hr><center>webserv/1.0.0s</center>\n</body>\n</html>\n";

        response.set_body(error_body);
    }
    next();
}
