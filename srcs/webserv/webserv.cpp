#include "../../includes/webserv.hpp"
#include "../../includes/PassiveHTTP.hpp"
#include "ActiveServer.hpp"
#include "serverBlock.hpp"

WebServ::WebServ() : _conf(){};

WebServ::WebServ(const WebServ &other){(void)other;};

WebServ::WebServ(const std::string&path){
	init(path);
};

WebServ::~WebServ(){};

WebServ &WebServ::operator=(const WebServ &other){(void)other;return *this;}




void WebServ::init(const std::string& path)
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
    //std::cout << "->" << _servers[0]._locations[0].get_cgi_bin() << std::endl; 
    //std::cout << "->" << _servers[0]._locations[0].get_cgi_ext() << std::endl; 

	for (std::vector<ServerBlock>::iterator it = _servers.begin(); it != _servers.end(); it++)
	{
		ServerConfig const& conf = it->get_server_conf();
		new PassiveHTTP<ActiveServer>(conf.get_host(), (uint16_t)conf.get_port(), *it, true);
	}
}

ServerBlocks const& WebServ::get_servers() const {
	return _servers;
}

std::ostream& operator<<(std::ostream& os, const WebServ& webserv) {
	return os << webserv.get_servers();
}
