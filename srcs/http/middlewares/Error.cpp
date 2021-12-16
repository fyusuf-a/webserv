#include "Middleware.hpp"
#include <sstream>
#include <stdio.h>
#include <string>


//405

void		Error::body(ActiveHTTP& serv, Request&, Response& response, MiddlewareChain& next) {

    int code = response.get_code();

	if (code >= 400)
    {
		if (code == 400)
			serv.setStatus(true);
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
