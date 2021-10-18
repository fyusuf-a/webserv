#include "../../includes/server.hpp"
#include "../../includes/parsingConf.hpp"

Server::Server(){}

Server::Server(const Server &other) : _serverConf(other._serverConf), _locations(other._locations) {}
Server::~Server(){}
    
Server &Server::operator=(const Server &other)
{
    if (this != &other)
        *this = other;
    return (*this);
}

ServerConfig const& Server::get_server_conf() const {
	return _serverConf;
}

Locations const& Server::get_locations() const {
	return _locations;
}

std::ostream& operator<<(std::ostream& os, const Server& server) {
	os << "server" << std::endl << "{" << std::endl;
	os << server.get_server_conf();
	Locations locations = server.get_locations();
	for(std::vector<ServerLocation>::const_iterator i = locations.begin()
			;i != locations.end(); i++) {
		os << *i;
	}
	os << "}" << std::endl;
	return os;
}
