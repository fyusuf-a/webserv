#ifndef SERVER_HPP
#define SERVER_HPP
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "serverConfig.hpp"
#include "serverLocation.hpp"

#define Locations std::vector<ServerLocation>


class ServerBlock
{

    public:
        ServerConfig        _serverConf;
        Locations           _locations;

    public:
        ServerBlock();
        ServerBlock(const ServerBlock &other);
        ~ServerBlock();
        ServerBlock &operator=(const ServerBlock &other);

		ServerConfig const& get_server_conf() const;
		Locations    const& get_locations() const;
};

std::ostream& operator<<(std::ostream& os, const ServerBlock& server);

#endif
