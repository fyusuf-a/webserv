#include "Middleware.hpp"

void		PathChopper::body(ActiveHTTP&, Request& request, Response& response, MiddlewareChain& next) {

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
    path = request.get_path();
    std::string cgi_ext = request.get_location().get_cgi_ext();
    loc = path.find(cgi_ext);
    if (loc != std::string::npos &&
        ( path[loc + cgi_ext.length()] == '/' || loc + cgi_ext.length() == path.length()))
            request.set_extra_path(path + loc + cgi_ext.length());

}