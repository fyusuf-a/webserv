#include "../webserv/webserv.hpp"
#include "../server/PassiveHTTP.hpp"
#include "../server/ActiveServer.hpp"
#include "../server/ActiveHTTP.hpp"
#include "../parsingConf/serverBlock.hpp"
#include "../utils/Log.hpp"

WebServ::WebServ() : _conf(){};

WebServ::WebServ(const WebServ &other){(void)other;};

WebServ::WebServ(const std::string&path){
	unsigned long int interfaces_launched = 0;
    _conf.parsing(path, this->_servers);

	for (std::vector<ServerBlock>::iterator it = _servers.begin(); it != _servers.end(); it++)
	{
	  	ServerConfig const& conf = it->get_server_conf();

        INetAddress interface(conf.getAddress(), conf.getPort());

	 	try {
	 		new PassiveHTTP<ActiveHTTP>(interface, &_servers, true);

	 		interfaces_launched++;
	 	}
	 	catch (std::runtime_error& e) {
	 	}
	}
	if (interfaces_launched == 0)
		throw(std::runtime_error("No interface was launched"));
};

WebServ::~WebServ(){};

WebServ &WebServ::operator=(const WebServ &other){(void)other;return *this;}

ServerBlocks const& WebServ::get_servers() const {
	return _servers;
}

std::ostream& operator<<(std::ostream& os, const WebServ& webserv) {

    ServerBlocks servers = webserv.get_servers();
	for(std::vector<ServerBlock>::const_iterator i = servers.begin()
			;i != servers.end(); i++) {
		os << *i;
	}
    return os;
}
