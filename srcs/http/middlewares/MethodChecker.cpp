#include "Middlewares.hpp"

//405
void		MethodChecker::body(ActiveHTTP& actHTTP, Request& request, Response& response, Middleware* next) {


	(void)response;
	(void)actHTTP;

    if (response.get_code() >= 400)
        next();

	bool set = false;

	for (std::vector<std::string>::const_iterator it = request.get_location().get_methods().begin(); it != request.get_location().get_methods().end(); it++)
	{
		if (*it == request.get_method())
			set = true;
	}

	if (set == false)
		response.set_code(Response::MethodNotAllowed);
	next();
}
