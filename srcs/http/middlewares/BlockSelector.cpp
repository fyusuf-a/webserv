#include "Middlewares.hpp"

void		BlockSelector::body(Request & request, Response & response, ServerBlocks const &serverBlocks, INetAddress const &interface) {
	
    (void)response;
    (void)interface;
    (void)request;
    (void)serverBlocks;

    bool            set = false;
    ServerBlocks    tmp_servers;
    Locations       tmp_locations;

// ---- Select server block

    for (std::vector<ServerBlock>::const_iterator it = serverBlocks.begin(); it != serverBlocks.end(); it++)
    {
        if ( ((it->_serverConf.getAddress() == interface.getAddress() || it->_serverConf.getAddress() == 0) && it->_serverConf.getPort() == interface.getPort() ) )
        {
                tmp_servers.push_back(*it);
        }
    }
    
    std::map<std::string, std::string> rqt_host = *request.get_header();
    
    for (std::vector<ServerBlock>::const_iterator it = tmp_servers.begin(); it != tmp_servers.end(); it++)
    {
        if (it->_serverConf.getName() == rqt_host["Host"] && it->_serverConf.getAddress() == interface.getAddress())
        {
            set = true;
            request.set_server(*it);
            tmp_servers.clear();
            break ;
       }
    }
    if (set == false) {
        for (std::vector<ServerBlock>::const_iterator it = tmp_servers.begin(); it != tmp_servers.end(); it++)
        {
            if (it->_serverConf.getAddress() == interface.getAddress() && it->_serverConf.getName() == "")
            {
                set = true;
                request.set_server(*it);
                tmp_servers.clear();
                break ;
            }
        }
    }
    if (set == false) {
        for (std::vector<ServerBlock>::const_iterator it = tmp_servers.begin(); it != tmp_servers.end(); it++)
        {
            if (it->_serverConf.getAddress() == 0 && it->_serverConf.getName() == rqt_host["Host"])
            {
                set = true;
                request.set_server(*it);
                tmp_servers.clear();
                break ;
            }
        }
    }
    if (set == false) {
        for (std::vector<ServerBlock>::const_iterator it = tmp_servers.begin(); it != tmp_servers.end(); it++)
        {
            if (it->_serverConf.getAddress() == 0 && it->_serverConf.getName() == "")
            {
                set = true;
                request.set_server(*it);
                tmp_servers.clear();
                break ;
            }
        }
    }
    if (set == false)
        throw (400);
    else
        set = false;

// ------ Select location block

    for (std::vector<ServerLocation>::const_iterator it = request.get_server()._locations.begin(); it != request.get_server()._locations.end(); it++)
    {
        if ( request.get_path() == it->get_location_path())
        {
            set = true;
            request.set_location(*it);
        }
    }
    if (set == false)
        throw (401);
}