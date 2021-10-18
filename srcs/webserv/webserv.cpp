#include "../../includes/webserv.hpp"

WebServ::WebServ() : _conf(){};

WebServ::WebServ(const WebServ &other){(void)other;};

WebServ::~WebServ(){};

WebServ &WebServ::operator=(const WebServ &other){(void)other;return *this;}




void WebServ::init(std::string path)
{
    try 
    {
        _conf.parsing(path, this->_servers);
    }
    catch(MyException& caught)
    {
        std::cout<<"[ERROR] " << caught.what() << std::endl;
    }
    // std::cout << "->" << _servers[0]._serverConf.get_host() << std::endl; 
    // std::cout << "->" << _servers[0]._serverConf.get_error() << std::endl; 
    
    // std::cout << "->" << _servers[0]._serverConf.get_name() << std::endl; 
    // std::cout << "->" << _servers[0]._locations[0].get_location_path() << std::endl; 
    // std::cout << "->" << _servers[0]._locations[1].get_location_path() << std::endl; 
    // std::cout << "->" << _servers[0]._locations[0].get_cgi_bin() << std::endl; 



}