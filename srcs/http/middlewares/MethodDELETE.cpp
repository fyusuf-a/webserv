# include "Middleware.hpp"
# include <stdio.h>

# define ERROR_PATH

Log& MethodDELETE::LOG = Log::getInstance();

//405
MethodDELETE::MethodDELETE(){
	
}

void		MethodDELETE::body(ActiveHTTP&, Request& request, Response& response, MiddlewareChain& next) {

// if body return 204
	if (response.get_code() >= 400 || request.get_method() != "DELETE" || request.get_is_script())
        next();
	else
	{
		if (access(request.get_path().c_str(), 0) != 0)
			response.set_code(Response::NotFound);
		else if (access(request.get_path().c_str(), 4) != 0)
			response.set_code(Response::Forbidden);
		else if ( remove(request.get_path().c_str()) != 0)
			LOG.error() << "error cant delete file" << std::endl;
	}
	next();
}
