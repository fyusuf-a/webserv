#include "Middleware.hpp"
#include <sstream>
#include <stdio.h>
#include <string>
#include "../tasks/GETTask.hpp"

//405

void		MethodGET::body(ActiveHTTP&serv, Request& request, Response& response, MiddlewareChain& next) {

	if (response.get_code() >= 400 || request.get_method() != "GET" || request.get_is_script())
        next();
	else
	{
		const char *filename = request.get_path().c_str();

		if (!Utils::is_file(filename) || access(filename, 0) != 0)
			response.set_code(Response::NotFound);
		else if (access(filename, 4) != 0)
			response.set_code(Response::Forbidden);
		else
		{
			std::string  body;
			std::string  result;

			//Get file size
			std::ifstream* file = new std::ifstream(filename, std::ios::binary);
			file->seekg(0, std::ios::end);
			ssize_t file_size = file->tellg();
			delete file;

			int  	fd;
			if ((fd = open(filename, O_RDONLY )) < 0)
				response.set_code(Response::Forbidden);
			else
			{
				std::ostringstream os;

				os << file_size;

				response.delete_header("Transfer-Encoding");
				response.set_header("Content-Length", os.str());

				new GETTask(fd, serv);
			}
		}
		next();

	}
}
