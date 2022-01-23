#include "Middleware.hpp"
#include "MiddlewareChain.hpp"
#include <algorithm>

//405

void		MethodChecker::body(ActiveHTTP& actHTTP, Request& request, Response& response, MiddlewareChain& next) {
	(void)response;
	(void)actHTTP;

    if (response.get_code() >= 400 || response.get_code() == 301){
        next();
        return ;
    }

	std::vector<std::string> methods = request.get_location().get_methods();
	std::string method = request.get_method();
	if (std::find(methods.begin(), methods.end(), method) == methods.end())
		response.set_code(Response::MethodNotAllowed);
	return next();
}
