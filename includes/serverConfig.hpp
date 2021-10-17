#ifndef SERVERCONFIG_HPP
#define SERVERCONFIG_HPP
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class ServerConfig
{

    private:
        uint32_t     			    _host;
		std::string					_name;
		std::string					_error;
		std::string					_server_root;
		int							_port;

        

    public:
        ServerConfig();
        ServerConfig(const ServerConfig &other);
        ~ServerConfig();
        ServerConfig &operator=(const ServerConfig &other);

        void            set_port(const int port);
        void            set_host(const uint32_t host);;
        void            set_name(std::string const &name);;
        void            set_root(std::string const &path);
        void            set_error(std::string const &error);

        int             get_port(void);
        uint32_t        get_host(void);
        std::string    const &get_name(void);
        std::string    const &get_root(void);
        std::string    const &get_error(void);


        void test(void);




};

#endif