#include "../../includes/server.hpp"

Server::Server() : _serverConf() {}

Server::Server(const Server &other) : _serverConf(other._serverConf), _locations(other._locations) {}
Server::~Server(){}
    
Server &Server::operator=(const Server &other)
{
    if (this != &other)
        *this = other;
    return (*this);
}


