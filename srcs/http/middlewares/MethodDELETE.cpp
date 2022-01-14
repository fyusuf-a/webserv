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
		int ret;
		if (access(request.get_path().c_str(), 0) != 0)
			response.set_code(Response::NotFound);
		else if (access(request.get_path().c_str(), 4) != 0)
			response.set_code(Response::Forbidden);
		else if ((ret = remove(request.get_path().c_str())) && ret)
			LOG.error() << "error cant delete file" << std::endl;
		if (!ret)
		{
			#ifdef TEST42
				response.set_code(200);
			#else
				response.set_code(204);
			#endif
		}
	}
	next();
}
