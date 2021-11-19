# include "Middleware.hpp"
# include <stdio.h>

//405

MethodPOST::MethodPOST() {
}

void		MethodPOST::body(ActiveHTTP&, Request& request, Response& response, MiddlewareChain& next) {

    if (response.get_code() >= 400 || request.get_method() != "POST")
        next();
	else
	{

	}
	next();
}