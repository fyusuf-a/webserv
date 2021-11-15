#include "Middlewares.hpp"

//405
void		MethodGET::body(ActiveHTTP& actHTTP, Request& request, Response& response, Middleware* next) {


	(void)response;
	(void)actHTTP;

    if (response.get_code() >= 400)
        next();


	next();
}
