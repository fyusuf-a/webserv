#include "../../includes/serverConfig.hpp"


ServerConfig::ServerConfig() : _host(0), _name(), _error(), _server_root(), _port(80){}

ServerConfig::ServerConfig(const ServerConfig &other) : _host(other._host), _name(other._name), _error(other._error), _server_root(other._server_root), _port(other._port)  {}
ServerConfig::~ServerConfig(){}
    
ServerConfig &ServerConfig::operator=(const ServerConfig &other)
{
    if (this != &other)
	{
		_host = other._host;
		_name = other._name;
		_error = other._error;
		_server_root = other._server_root;
		_port = other._port;
	}
    return (*this);
}

void            ServerConfig::set_port(const int port){ this->_port = port; }
void            ServerConfig::set_host(const uint32_t host){ this->_host = host; }
void            ServerConfig::set_name(std::string const &name){ this->_name = name; }
void            ServerConfig::set_error(std::string const &error){ this->_error = error; }
void            ServerConfig::set_root(std::string const &server_root){ this->_server_root = server_root; }

int                  ServerConfig::get_port(void) const{ return (this->_port); }
uint32_t             ServerConfig::get_host(void) const{ return (this->_host); }
std::string const   &ServerConfig::get_name(void) const{ return (this->_name); }
std::string const   &ServerConfig::get_error(void) const{ return (this->_error); }

std::string const   &ServerConfig::get_root(void) const{ return (this->_server_root); }

std::ostream& operator<<(std::ostream& os, const ServerConfig& config) {
	os << "listen\t" << config.get_port() << ";" << std::endl;
	os << "host\t" << config.get_host() << ";" << std::endl;
	if (!config.get_name().empty())
		os << "server_name\t" << config.get_name() << ";" << std::endl;
	if (!config.get_error().empty())
		os << "error\t" << config.get_error() << ";" << std::endl;
	if (!config.get_root().empty())
		os << "root\t" << config.get_root() << ";" << std::endl;
	return os;
}
