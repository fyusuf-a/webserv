#include "Middleware.hpp"

void		ExtractQuery::body(ActiveHTTP&, Request& request, Response& response, MiddlewareChain& next) {

    if (response.get_code() >= 400){
        next();
        return ;
    }
    
    std::string path = request.get_path();
    std::size_t loc = path.find('?');

    if (loc != std::string::npos) {
        request.set_query(path.substr(loc + 1));
        request.set_path(path.substr(0, loc));
    }

    next();
}