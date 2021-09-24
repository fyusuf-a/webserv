#ifndef SERVERCONFIG_HPP
#define SERVERCONFIG_HPP
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class ServerConfig
{

    private:
        std::string					_host;
		std::string					_name;
		std::string					_server_root;
		int							_port;

        

    public:
        ServerConfig();
        ServerConfig(const ServerConfig &other);
        ~ServerConfig();
        ServerConfig &operator=(const ServerConfig &other);

        void            set_port(const int port);
        void            set_host(std::string const &ip);;
        void            set_name(std::string const &name);;
        void            set_root(std::string const &path);

        int             get_port(void);
        std::string    const &get_host(void);
        std::string    const &get_name(void);
        std::string    const &get_root(void);

        void test(void);




};

#endif