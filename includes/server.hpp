#ifndef SERVER_HPP
#define SERVER_HPP
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "serverConfig.hpp"

class Server
{

    public:
        ServerConfig _serverConf;

    public:
        Server();
        // Server(const Server &other);
        // ~Server();
        Server &operator=(const Server &other);

};

#endif