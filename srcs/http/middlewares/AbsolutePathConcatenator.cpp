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
	//std::cout<<request.get_server()<<"//////"<<std::endl;
	//std::cout << request.get_location().get_root() << std::endl;
	//std::cout << request.get_location().get_location_path() << std::endl;
	//std::cout << request.get_location().get_auto_index() << std::endl;
	//std::cout << request.get_location().get_cgi_ext() << std::endl;
	if (request.get_location().get_root() != "")
		absolute_path = request.get_location().get_root() + request.get_path();
	else if (request.get_server().get_server_conf().getRoot() == "")
		absolute_path = "";
	else
		absolute_path = request.get_server().get_server_conf().getRoot() + request.get_path();

	request.set_path(absolute_path);
	//std::cout << absolute_path << std::endl;
	next();
}
