#include "Middleware.hpp"
#include "MiddlewareChain.hpp"

AbsolutePathConcatenator::AbsolutePathConcatenator() {
}

std::string get_absolute_path(Request &request, const std::string &path) {
	std::string absolute_path;

	if (request.get_location().get_root() != "")
		absolute_path = request.get_location().get_root() + path;
	else if (request.get_server().get_server_conf().getRoot() == "")
		absolute_path = "";
	else
		absolute_path = request.get_server().get_server_conf().getRoot() + path;
	return (absolute_path);
}

void		AbsolutePathConcatenator::body(ActiveHTTP& actHTTP, Request& request, Response& response, MiddlewareChain& next) {
	
	(void)response;
	(void)actHTTP;

    if (response.get_code() >= 400) {
        next();
        return ;
    }

    request.set_original_request_path(request.get_path());
	request.set_path(get_absolute_path(request, request.get_original_request_path()));
	next();
}
