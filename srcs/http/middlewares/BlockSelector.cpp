#include "Middlewares.hpp"

void		BlockSelector::body(Request & request, Response & response, ServerBlocks const &serverBlocks, INetAddress const* interface) {
	
    (void)response;
    (void)interface;
    (void)request;
    (void)serverBlocks;

	std::string ip = request.get_method();
	std::string server_name = request.get_method();

    for (std::vector<ServerBlock>::const_iterator it = serverBlocks.begin(); it != serverBlocks.end(); it++)
    {
        // if (it->_serverConf.get_host() == interface->getAddress())
        // {
            std::cout << "bonjour" << std::endl;
        // }
    }


}