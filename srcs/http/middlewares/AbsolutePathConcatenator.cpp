#include "Middleware.hpp"
#include "MiddlewareChain.hpp"

std::string get_absolute_path(Request &request, const std::string &path) {
	
	std::string absolute_path;

 	if (request.get_location().get_root() != "")
	{
		absolute_path = request.get_location().get_root();
		
		std::string location_path = request.get_location().get_location_path();

		if (absolute_path.back() != '/')
			absolute_path += "/";
		size_t i = 0;

		for (; path[i] == location_path[i]; i++);

		if (i < path.size())
			absolute_path += &(path[i]);

		if (absolute_path.back() != '/' && Utils::is_dir(absolute_path.c_str()))
			absolute_path += "/";

	}
	else if (request.get_server().get_server_conf().getRoot() == "")
		absolute_path = "";
	else
		absolute_path = request.get_server().get_server_conf().getRoot() + request.get_path();
	return (absolute_path);
}

void		AbsolutePathConcatenator::body(ActiveHTTP&, Request& request, Response& response, MiddlewareChain& next) {
	
    if (response.get_code() >= 400) {
        next();
        return ;
    }

    request.set_original_request_path(request.get_path());
	request.set_path(get_absolute_path(request, request.get_original_request_path()));
	next();
}
