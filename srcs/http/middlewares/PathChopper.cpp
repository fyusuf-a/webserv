#include "Middleware.hpp"
#include <sys/stat.h>

int         is_script(Request& request, std::string path) {
    std::string absolute_path = get_absolute_path(request, path);

    struct stat s;
    if (!stat(absolute_path.c_str(), &s)) {
        if (s.st_mode & S_IFDIR)
            return (0);
        return (1);
    }
    else
        return (0);
}

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
    std::size_t head = 0;

    while (1) {
        loc = path.find(cgi_ext, head);
        if (loc == std::string::npos ||
            (path[loc + cgi_ext.length()] != '/' && loc + cgi_ext.length() != path.length())) {
                next();
                return;
        }
        if (is_script(request, path.substr(0, loc + cgi_ext.length())))
            break;
        head = loc + 1;
    }
    request.set_extra_path(path.substr(loc + cgi_ext.length()));
    request.set_path(path.substr(0, loc + cgi_ext.length()));
    std::cout << request.get_path() << "||" << request.get_extra_path() << "||" << request.get_query() << std::endl;

    next();
}