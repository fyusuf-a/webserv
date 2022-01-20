# include "Middleware.hpp"
# include <stdio.h>

# define ERROR_PATH

Log& MethodDELETE::LOG = Log::getInstance();

//405

void		MethodDELETE::body(ActiveHTTP&, Request& request, Response& response, MiddlewareChain& next) {

// if body return 204
	if (response.get_code() >= 400 || request.get_method() != "DELETE" || request.get_is_script())
        return next();
	else
	{
		int ret = 0;
		std::string path =request.get_path();
		
		if (access(path.c_str(), 0) != 0)
		{
			response.set_code(Response::NotFound);
			return next();
		}
		else if (access(path.c_str(), 4) != 0)
		{
			response.set_code(Response::Forbidden);
			return next();

		}
		else if ((ret = remove(path.c_str())) && ret == -1)
			LOG.error() << "error cant delete file" << std::endl;
		if (!ret)
		{
			#ifdef TEST42
				response.set_code(Response::OK);
			#else
				response.set_code(Response::NoContent);
			#endif
		}
	}
	next();
}
