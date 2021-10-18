#ifndef SERVERCONFIG_HPP
#define SERVERCONFIG_HPP
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdint.h>


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

        int             get_port(void) const;
        uint32_t        get_host(void) const;
        std::string    const &get_name(void) const;
        std::string    const &get_root(void) const;
        std::string    const &get_error(void) const;


        void test(void);




};

std::ostream& operator<<(std::ostream& os, const ServerConfig& config);

#endif
