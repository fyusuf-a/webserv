# include "Middleware.hpp"
# include <stdio.h>
# include "GETTask.hpp"

//405

MethodGET::MethodGET() {
}

void		MethodGET::body(ActiveHTTP&, Request& request, Response& response, MiddlewareChain& next) {

    if (response.get_code() >= 400 || request.get_method() != "GET")
        next();
	else
	{
		if (access(request.get_path().c_str(), 0) != 0)
			response.set_code(Response::NotFound);
		else if (access(request.get_path().c_str(), 4) != 0)
			response.set_code(Response::Forbidden);
		else
		{
			std::string  body;
			std::string  result;

			int  	fd;

			if ((fd = open(request.get_path().c_str(), O_RDONLY )) < 0 )
				response.set_code(Response::Forbidden);
			else
				new GETTask(fd, &next);
			
		}

	}
	next();
}