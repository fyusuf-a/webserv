#include "Middleware.hpp"

void		IndexSelector::body(ActiveHTTP&, Request& request, Response& response, MiddlewareChain& next) {


    if (response.get_code() >= 400 || request.get_path().back() != '/'){
        next();
        return ;
    }

    std::vector<std::string> indexes_loc = request.get_location().get_index();
    std::vector<std::string> indexes_serv = request.get_server().get_server_conf().getIndex();
    std::string path = request.get_path();
    std::string idx;

    for (std::vector<std::string>::const_iterator it = indexes_serv.begin(); it != indexes_serv.end(); it++)
    {        if ( access((path + *it).c_str(), F_OK ) != -1)
            idx = path + *it;
    }

    for (std::vector<std::string>::const_iterator it = indexes_loc.begin(); it != indexes_loc.end(); it++)
    {
        if ( access((path + *it).c_str(), F_OK ) != -1)
            idx = path + *it;
    }

    if (idx != "")
        request.set_path(idx);
    else if (request.get_location().get_auto_index() == false)
        response.set_code(Response::Forbidden);
    next();
}