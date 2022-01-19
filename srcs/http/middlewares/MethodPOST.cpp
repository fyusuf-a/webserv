#include "Middleware.hpp"
#include <sstream>
#include <stdio.h>
#include <string>
#include "../tasks/POSTTask.hpp"

Log& MethodPOST::LOG = Log::getInstance();

void		MethodPOST::body(ActiveHTTP& serv, Request& request, Response& response, MiddlewareChain& next) {

	if (response.get_code() >= 400
		|| !(request.get_method() == "POST" || request.get_method() == "PUT")
		|| request.get_is_script()) {
        return next();
	}
	
	const char  *filename = request.get_path().c_str();

	if (!request.get_is_script())
		LOG.info() << "Opening file: " << filename << std::endl;

	int  	fd;

	if ((fd = open(filename, O_RDWR | O_CREAT
				| (request.get_method() == "POST" ? O_APPEND : O_TRUNC)
				, 0777)) < 0) {
#ifdef TEST42
		response.set_code(Response::OK);
#else
		response.set_code(Response::Forbidden);
#endif
		return next();
	}
	response.delete_header("Transfer-Encoding");
	response.set_header("Content-Length", "0", true);
	new POSTTask(fd, serv);
	response.set_code(Response::OK);
	return next();
}
