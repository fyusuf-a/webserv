#include "Middleware.hpp"

BlockSelector::BlockSelector() {
}

void		BlockSelector::body(ActiveHTTP& actHTTP, Request& request, Response& response, MiddlewareChain& next) {

	(void)request;

	if (response.get_code() >= 400)
	{
        next();
        return ;
	}

	bool            set = false;
	ServerBlocks    tmp_servers;
	Locations       tmp_locations;
	ServerBlocks	serverBlocks = *actHTTP.getServerBlocks();
	INetAddress		interface = actHTTP.getInterface();

	// ---- Select server block

	for (std::vector<ServerBlock>::const_iterator it = serverBlocks.begin(); it != serverBlocks.end(); it++)
	{
		if ( ((it->_serverConf.getAddress() == interface.getAddress() || it->_serverConf.getAddress() == 0) && it->_serverConf.getPort() == interface.getPort() ) )
		{
			tmp_servers.push_back(*it);
		}
	}

	std::map<std::string, std::string> rqt_host = request.get_header();

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
	if (set == false) {
		response.set_code(Response::BadRequest);
		next();
		return ;
	}
	else
		set = false;

	// ------ Select location block

	for (std::vector<ServerLocation>::const_iterator it = request.get_server()._locations.begin(); it != request.get_server()._locations.end(); it++)
	{
		if ( request.get_path() == it->get_location_path() && !set)
		{
			set = true;
			request.set_location(*it);
		}
	}

	int result = 1;

	if ( set == false ) {
		for (std::vector<ServerLocation>::const_iterator it = request.get_server()._locations.begin(); it != request.get_server()._locations.end(); )
		{
			if (  request.get_path() < it->get_location_path())
				it++;
			else
				tmp_locations.push_back(*it++);
		}

		for (std::vector<ServerLocation>::const_iterator it = tmp_locations.begin(); it != tmp_locations.end(); it++){

			if ( Utils::ft_find(it->get_location_path(),  request.get_path()) > result)
			{
				result =  Utils::ft_find(it->get_location_path(),  request.get_path());
				request.set_location(*it);
				set = true;
			}
		}
	}

	if ( result == 1 )
	{
		for (std::vector<ServerLocation>::const_iterator it = tmp_locations.begin(); it != tmp_locations.end(); it++){

			if ( it->get_location_path() == "/" )
			{
				set = true;
				request.set_location(*it);
			}
		}
	}

	if (set == false) {
		std::cout << "in" << std::endl;
		response.set_code(Response::NotFound);
	}
	next();
}
