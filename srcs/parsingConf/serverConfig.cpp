#include "serverConfig.hpp"


ServerConfig::ServerConfig() : _host(0), _name(), _error(), _server_root(), _port(80), _ip_already_set(false) {}

ServerConfig::ServerConfig(const ServerConfig &other) : _host(other._host), _name(other._name), _error(other._error), _server_root(other._server_root), _port(other._port),
	_ip_already_set(other._ip_already_set) {}
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
		_ip_already_set = other._ip_already_set;
	}
    return (*this);
}

void            ServerConfig::setPort(const uint16_t port){ this->_port = port; }
void            ServerConfig::setAddress(IPAddress const &host){ this->_host = host; }
void            ServerConfig::setName(std::string const &name){ this->_name = name; }
void            ServerConfig::setError(std::string const &error){ this->_error = error; }
void            ServerConfig::setRoot(std::string const &server_root){ this->_server_root = server_root; }
void            ServerConfig::setIP_already_set(bool my_bool) {_ip_already_set = my_bool;}

uint16_t             ServerConfig::getPort(void) const { return (this->_port); }
IPAddress const   	&ServerConfig::getAddress(void) const { return (this->_host); }
std::string const   &ServerConfig::getName(void) const { return (this->_name); }
std::string const   &ServerConfig::getError(void) const { return (this->_error); }
std::string const   &ServerConfig::getRoot(void) const { return (this->_server_root); }
bool				ServerConfig::getIP_already_set(void) const { return (this->_ip_already_set); }

std::ostream& operator<<(std::ostream& os, const ServerConfig& config) {
	os << "listen\t" << config.getPort() << ";" << std::endl;
	os << "host\t" << config.getAddress() << ";" << std::endl;
	if (!config.getName().empty())
		os << "server_name\t" << config.getName() << ";" << std::endl;
	if (!config.getError().empty())
		os << "error\t" << config.getError() << ";" << std::endl;
	if (!config.getRoot().empty())
		os << "root\t" << config.getRoot() << ";" << std::endl;
	return os;
}


