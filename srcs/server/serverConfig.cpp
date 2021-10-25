#include "../../includes/serverConfig.hpp"


ServerConfig::ServerConfig() : _host(), _name(), _error(), _server_root(), _port(80){}

ServerConfig::ServerConfig(const ServerConfig &other) : _host(other._host), _name(other._name), _error(other._error), _server_root(other._server_root), _port(other._port)  {}
ServerConfig::~ServerConfig(){}
    
ServerConfig &ServerConfig::operator=(const ServerConfig &other)
{
    if (this != &other)
        *this = other;
    return (*this);
}

void            ServerConfig::set_port(const uint16_t port){ this->_port = port; }
void            ServerConfig::set_host(std::string const &host){ this->_host = host; }
void            ServerConfig::set_name(std::string const &name){ this->_name = name; }
void            ServerConfig::set_error(std::string const &error){ this->_error = error; }
void            ServerConfig::set_root(std::string const &server_root){ this->_server_root = server_root; }

uint16_t             ServerConfig::get_port(void){ return (this->_port); }
std::string const   &ServerConfig::get_host(void){ return (this->_host); }
std::string const   &ServerConfig::get_name(void){ return (this->_name); }
std::string const   &ServerConfig::get_error(void){ return (this->_error); }

std::string const   &ServerConfig::get_root(void){ return (this->_server_root); }



