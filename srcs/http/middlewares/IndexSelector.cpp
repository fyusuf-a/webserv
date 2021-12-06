#include "Middleware.hpp"


void		IndexSelector::body(ActiveHTTP&, Request& request, Response& response, MiddlewareChain& next) {


    if (response.get_code() >= 400/* || request.get_path()[request.get_path().size()] != '/'*/ || request.get_method() != "GET"){
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
    std::cout << "--->" << idx << std::endl;
    if (idx != "")
        request.set_path(idx);
    if (request.get_location().get_auto_index() == false)
        response.set_code(Response::Forbidden);
    next();
}