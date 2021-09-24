#include "../../includes/webserv.hpp"

WebServ::WebServ() : _conf(){};

WebServ::WebServ(const WebServ &other){};

WebServ::~WebServ(){};

WebServ &WebServ::operator=(const WebServ &other){return *this;};




void WebServ::init(std::string path)
{
    _conf.parsing(path, this->_servers);
    std::cout << "->" << _servers[0]._serverConf.get_host() << std::endl; 
}