#include "../../includes/server.hpp"

Server::Server() : _serverConf() {}

// Server::Server(const Server &other){}
// Server::~Server(){}
    
Server &Server::operator=(const Server &other)
{
    if (this != &other)
        *this = other;
    return (*this);
}


