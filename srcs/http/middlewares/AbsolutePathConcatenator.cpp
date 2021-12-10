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

	// std::cout << "location.get_root -> " << request.get_location() << "///" << std::endl;
 	if (request.get_location().get_root() != "")
	{
		// if location have a root directive location path = root direcitve (it was += previsously)
		// example :
		// 	location /directory {
		//		root /mypath/to/folder;
		//	}
		// --> absolute = /mypath/to/folder/;

	
		absolute_path = request.get_location().get_root()/* + request.get_path()*/;
		std::string request_path = request.get_path();
		std::string location_path = request.get_location().get_location_path();

		if (absolute_path.back() != '/')
			absolute_path += "/";
		size_t i = 0;

		// this time example :
		// GET /directory/myfile HTTTP/1.1

		// 	location /directory {
		//		root /mypath/to/folder;
		//	}
		// --> absolute = /mypath/to/folder/"myfile";

		for (; request_path[i] == location_path[i]; i++);

		if ((i + 1) < request_path.size())
			absolute_path += &(request_path[i+1]);

		if (absolute_path.back() != '/' && Utils::is_dir(absolute_path.c_str()))
			absolute_path += "/";

	}
	else if (request.get_server().get_server_conf().getRoot() == "")
		absolute_path = "";
	else
		absolute_path = request.get_server().get_server_conf().getRoot() + request.get_path();

	request.set_path(absolute_path);


	next();
}
