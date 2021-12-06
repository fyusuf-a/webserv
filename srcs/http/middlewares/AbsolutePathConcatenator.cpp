#include "Middleware.hpp"
#include "MiddlewareChain.hpp"

AbsolutePathConcatenator::AbsolutePathConcatenator() {
}

void		AbsolutePathConcatenator::body(ActiveHTTP& actHTTP, Request& request, Response& response, MiddlewareChain& next) {
	
	(void)response;
	(void)actHTTP;

    if (response.get_code() >= 400) {
        next();
        return ;
    }

	std::string absolute_path;

	if (request.get_location().get_root() != "")
		absolute_path = request.get_location().get_root() + request.get_path();
	else
		absolute_path = request.get_server().get_server_conf().getRoot() + request.get_path();

	request.set_path(absolute_path);
	next();
}
