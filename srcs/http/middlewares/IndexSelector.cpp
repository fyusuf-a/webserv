#include "Middleware.hpp"

Log& IndexSelector::LOG = Log::getInstance();

void		IndexSelector::body(ActiveHTTP&, Request& request, Response& response, MiddlewareChain& next) {

    if (response.get_code() >= 400 || response.get_code() == 301
		|| *(request.get_path().end() - 1) != '/'
		|| !(request.get_method() == "GET" || request.get_method() == "HEAD" || request.get_is_script())) {
        next();
        return ;
    }

    std::vector<std::string> indexes = request.get_location().get_index();
    std::string path = request.get_path();
    std::string idx;

    for (std::vector<std::string>::const_iterator it = indexes.begin(); it != indexes.end(); it++)
    {

        if ( access((path + *it).c_str(), F_OK ) != -1)
            idx = path + *it;
    }
    if (idx != "")
        request.set_path(idx);

    else if (request.get_location().get_auto_index() == false)
	{
		LOG.debug() << "Autoindex is off" << std::endl;
        response.set_code(Response::NotFound);
    }
    else
        response.set_index_display(true);

    next();
}
