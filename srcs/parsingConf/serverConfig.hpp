#ifndef SERVERCONFIG_HPP
#define SERVERCONFIG_HPP
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include "../ipaddress/IPAddress.hpp"


class ServerConfig
{

    private:
        IPAddress  			    _host;
		std::string					_name;
		std::string					_error;
		std::string					_server_root;
		uint16_t                	_port;
                bool                            _ip_already_set;


        

    public:
        ServerConfig();
        ServerConfig(const ServerConfig &other);
        ~ServerConfig();
        ServerConfig &operator=(const ServerConfig &other);

        void            set_port(const uint16_t port);
        void            set_host(const IPAddress& host);
        void            set_name(std::string const &name);;
        void            set_root(std::string const &path);
        void            set_error(std::string const &error);
        void            set_ip_already_set(bool error);

        const uint16_t& get_port(void) const;
        IPAddress      const &get_host(void) const;
        std::string    const &get_name(void) const;
        std::string    const &get_root(void) const;
        std::string    const &get_error(void) const;
        bool           get_ip_already_set(void) const;

void set_host(std::string const &n);



        void test(void);




};

std::ostream& operator<<(std::ostream& os, const ServerConfig& config);

#endif
