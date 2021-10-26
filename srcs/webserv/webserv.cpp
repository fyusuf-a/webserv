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

    _conf.parsing(path, this->_servers);

	for (std::vector<ServerBlock>::iterator it = _servers.begin(); it != _servers.end(); it++)
	{
		ServerConfig const& conf = it->get_server_conf();
        INetAddress interface(conf.get_host(), conf.get_port());
		new PassiveHTTP<ActiveServer>(interface, *it, true);
	}
}

ServerBlocks const& WebServ::get_servers() const {
	return _servers;
}

std::ostream& operator<<(std::ostream& os, const WebServ& webserv) {
	return os << webserv.get_servers();
}
