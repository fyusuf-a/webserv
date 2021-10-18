#ifndef SERVER_HPP
#define SERVER_HPP
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "serverConfig.hpp"
#include "serverLocation.hpp"

#define Locations std::vector<ServerLocation>


class Server
{

    public:
        ServerConfig        _serverConf;
        Locations           _locations;

    public:
        Server();
        Server(const Server &other);
        ~Server();
        Server &operator=(const Server &other);

};

#endif
