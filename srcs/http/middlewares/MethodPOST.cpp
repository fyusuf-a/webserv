#include "Middleware.hpp"
#include <sstream>
#include <stdio.h>
#include <string>
#include "../tasks/POSTTask.hpp"

//405

void		MethodPOST::body(ActiveHTTP& serv, Request& request, Response& response, MiddlewareChain& next) {

	if (response.get_code() >= 400 || request.get_method() != "POST" || request.get_is_script()) {
        next();
	}
	else
	{
		std::string  body;
		std::string  result;

		const char  *filename = request.get_path().c_str();

		int  	fd;


		response.delete_header("Transfer-Encoding");
		response.set_header("Content-Length", "0");

		if ((fd = open(filename, O_RDWR | O_APPEND | O_CREAT, 0777)) < 0)
			response.set_code(Response::Forbidden);
		else
		{
			new POSTTask(fd, serv);
			response.set_code(Response::Created);
		}
		next();
	}
}
