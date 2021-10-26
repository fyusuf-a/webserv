#include "../../includes/webserv.hpp"

WebServ::WebServ() : _conf(){};

WebServ::WebServ(const WebServ &other){(void)other;};

WebServ::~WebServ(){};

WebServ &WebServ::operator=(const WebServ &other){(void)other;return *this;}




void WebServ::init(std::string path)
{
    _conf.parsing(path, this->_servers);


    std::cout << "host ->" << _servers[0]._serverConf.get_host() << std::endl; 

    std::cout << "port ->" << _servers[0]._serverConf.get_port() << std::endl; 
    std::cout << "error ->" << _servers[0]._serverConf.get_error() << std::endl; 
    
    std::cout << "name ->" << _servers[0]._serverConf.get_name() << std::endl; 
    std::cout << "l path ->" << _servers[0]._locations[0].get_location_path() << std::endl; 
    std::cout << "cgi_bin ->" << _servers[0]._locations[0].get_cgi_bin() << std::endl; 
    std::cout << "cgi_ext ->" << _servers[0]._locations[0].get_cgi_ext() << std::endl;
    std::cout << "roooot ->" << _servers[0]._locations[0].get_root() << std::endl; 

std::vector<std::string> tmp = _servers[0]._locations[0].get_index();
    for (size_t i = 0; i < tmp.size();i++)
        std::cout << tmp[i] << std::endl;



}