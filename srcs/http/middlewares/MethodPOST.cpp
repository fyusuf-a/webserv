#include "Middleware.hpp"
#include <sstream>
#include <stdio.h>
#include <string>
#include "../tasks/POSTTask.hpp"

//405

MethodPOST::MethodPOST() {
}

void		MethodPOST::body(ActiveHTTP& serv, Request& request, Response& response, MiddlewareChain& next) {

	if (response.get_code() >= 400 || request.get_method() != "POST")
        next();
	else
	{
		std::string  body;
		std::string  result;

		std::string	filepath = request.get_path();


		int  	fd;
		if ((fd = open(filepath.c_str(), O_RDWR | O_APPEND | O_CREAT, 0777)) < 0) {
			response.set_code(Response::Forbidden);
		}
		else
			new POSTTask(fd, &serv);
		next();
	}
}
