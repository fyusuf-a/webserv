# include "Middleware.hpp"
# include <stdio.h>

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

			std::ifstream fd(request.get_path());

			if (!fd.is_open() || !fd.good())
				response.set_code(Response::Forbidden);
			for (int i = 0; getline(fd, body); i++)
            {
                if (i)
                	result += '\n';
                result += body;
            }
			response.set_body(result);

		}

	}
	next();
}
