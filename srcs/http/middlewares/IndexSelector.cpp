#include "Middlewares.hpp"

IndexSelector::IndexSelector() {

}

void		IndexSelector::body(ActiveHTTP&, Request& request, Response&, MiddlewareChain& next) {

    (void)response;
    (void)interface;
    (void)request;
    (void)serverBlocks;

    if (response.get_code() >= 400 || request.get_path().back() != '/'){
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
    if (request.get_location().get_auto_index() == false && idx != "")
        response.set_code(Response::Forbidden);
    next();
}