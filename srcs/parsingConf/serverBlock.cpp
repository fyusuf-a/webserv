#include "../../includes/serverBlock.hpp"
#include "../../includes/parsingConf.hpp"

ServerBlock::ServerBlock(){}

ServerBlock::ServerBlock(const ServerBlock &other) : _serverConf(other._serverConf), _locations(other._locations) {}
ServerBlock::~ServerBlock(){}
    
ServerBlock &ServerBlock::operator=(const ServerBlock &other)
{
    if (this != &other)
        *this = other;
    return (*this);
}

ServerConfig const& ServerBlock::get_server_conf() const {
	return _serverConf;
}

Locations const& ServerBlock::get_locations() const {
	return _locations;
}

std::ostream& operator<<(std::ostream& os, const ServerBlock& server) {
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
