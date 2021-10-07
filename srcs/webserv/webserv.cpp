#include "../../includes/webserv.hpp"

WebServ::WebServ() : _conf(){};

WebServ::WebServ(const WebServ &other){(void)other;};

WebServ::~WebServ(){};

WebServ &WebServ::operator=(const WebServ &other){(void)other;return *this;}




void WebServ::init(std::string path)
{
    _conf.parsing(path, this->_servers);
    std::cout << "->" << _servers[0]._serverConf.get_host() << std::endl; 
    std::cout << "->" << _servers[0]._serverConf.get_error() << std::endl; 
    std::cout << "->" << _servers[0]._serverConf.get_name() << std::endl; 


}