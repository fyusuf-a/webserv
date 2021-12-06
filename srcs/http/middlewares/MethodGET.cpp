#include "Middleware.hpp"
#include <sstream>
#include <stdio.h>
#include <string>
#include "../tasks/GETTask.hpp"

//405

MethodGET::MethodGET() {
}

void		MethodGET::body(ActiveHTTP&serv, Request& request, Response& response, MiddlewareChain& next) {

	if (response.get_code() >= 400 || request.get_method() != "GET")
        next();
	else
	{
		std::cout << "-->" << request.get_path() << std::endl;
		if (!Utils::is_file(request.get_path().c_str()) || access(request.get_path().c_str(), 0) != 0)
		{
			std::cout << "is not file" << std::endl;
			response.set_code(Response::NotFound);
		}
		else if (access(request.get_path().c_str(), 4) != 0)
			response.set_code(Response::Forbidden);
		else
		{
			std::string  body;
			std::string  result;

			std::string	filepath = request.get_path();

			//Get file size
			std::ifstream* file = new std::ifstream(filepath.c_str(), std::ios::binary);
			file->seekg(0, std::ios::end);
			ssize_t file_size = file->tellg();
			delete file;

			int  	fd;
			if ((fd = open(filepath.c_str(), O_RDONLY )) < 0)
				response.set_code(Response::Forbidden);
			else
			{
				std::ostringstream os;
				os << file_size;
				response.delete_header("Transfer-Encoding");
				response.set_header("Content-Length", os.str());
				//new GETTask(fd, &serv, file_size);
				new GETTask(fd, &serv);
			}
		}
		next();

	}
}
