#include "Middlewares.hpp"


//405
void		BlockSelector::body(Request & request, Response & response, ServerBlocks const &serverBlocks, INetAddress const &interface) {
	
    (void)response;
    (void)interface;
    (void)request;
    (void)serverBlocks;

    bool set = false;

    for (std::vector<std::string>::const_iterator it = request.get_location().get_methods().begin(); it != request.get_location().get_methods().end(); it++)
    {
        if (*it == request.get_method())
        {
            set = true;
            std::cout << *it << std::endl;
        }
    }

    if (set == false)
        throw (405);
}