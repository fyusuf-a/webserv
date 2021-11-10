#include "Middlewares.hpp"

void		BlockSelector::body(Request & request, Response & response, ServerBlocks const &serverBlocks, INetAddress const &interface) {
	
    (void)response;
    (void)interface;
    (void)request;
    (void)serverBlocks;

    ServerBlocks    tmp_servers;
    Locations       tmp_locations;

// ---- Select server block

    for (std::vector<ServerBlock>::const_iterator it = serverBlocks.begin(); it != serverBlocks.end(); it++)
    {
        if ( ((it->_serverConf.getAddress() == interface.getAddress() || it->_serverConf.getAddress() == 0) && it->_serverConf.getPort() == interface.getPort() ) )
        {
            std::cout << "->" << it->_serverConf.getName() << std::endl;
            tmp_servers.push_back(*it);
        }
    }
    
    std::map<std::string, std::string> rqt_host = *request.get_header();
    
    for (std::vector<ServerBlock>::const_iterator it = tmp_servers.begin(); it != tmp_servers.end(); it++)
    {
       if (it->_serverConf.getName() == rqt_host["Host"])
       {
            request.set_server(*it);
            tmp_servers.clear();
            break ;
       }
    }
// ------ Select location block
    
    // std::cout << request.get_server()._serverConf.getName() << std::endl;

    // for (std::vector<ServerLocation>::const_iterator it = request.get_server()._locations.begin(); it != request.get_server()._locations.end(); it++)
    // {
    //     if ( true )
    //     {
    //         tmp_locations.push_back(*it);
    //     }
    // }
    
    // for (std::vector<ServerLocation>::const_iterator it = tmp_locations.begin(); it != tmp_locations.end(); it++)
    // {
    //    if ( true )
    //    {
    //        std::cout << it[0].get_cgi_bin() << std::endl;
    //         request.set_location(*it);
    //         tmp_servers.clear();
    //         break ;
    //    }
    // }
}