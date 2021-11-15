#include "Middlewares.hpp"

void		IndexSelector::body(Request & request, Response & response, ServerBlocks const &serverBlocks, INetAddress const &interface) {

    (void)response;
    (void)interface;
    (void)request;
    (void)serverBlocks;


    if (request.get_path().back() != '/')
        return ;

    std::vector<std::string> indexes = request.get_location().get_index();
    std::string path = request.get_location().get_location_path() + request.get_location().get_root();
    std::string idx;

    for (std::vector<std::string>::const_iterator it = indexes.begin(); it != indexes.end(); it++)
    {
        if ( access((path + *it).c_str(), F_OK ) != -1)
            idx = path + *it;
    }

    if (idx != "")
        return ;
    if (_auto_index == false)
        response.set_code(Response::Forbidden);

}