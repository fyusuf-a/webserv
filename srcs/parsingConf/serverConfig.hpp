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
        IPAddress  			        _host;
		std::string				    _name;
		std::string				    _error;
		std::string				    _server_root;
		uint16_t                    _port;
        bool                        _ip_already_set;
        std::vector<std::string>	_index;
        std::string					_cgi_ext_s;
		std::string					_cgi_bin_s;


        

    public:
        ServerConfig();
        ServerConfig(const ServerConfig &other);
        ~ServerConfig();
        ServerConfig &operator=(const ServerConfig &other);

        void            setPort(const uint16_t port);
        void            setAddress(const IPAddress& host);
        void            setName(std::string const &name);;
        void            setRoot(std::string const &path);
        void            setError(std::string const &error);
        void            setIP_already_set(bool error);
        void            setIndex(std::vector<std::string> const &index);

        void            set_cgi_ext(std::string const &cgi_ext);
        void            set_cgi_bin(std::string const &cgi_bin);

        

        uint16_t                        getPort(void) const;
        IPAddress   const               &getAddress(void) const;
        std::string const               &getName(void) const;
        std::string const               &getRoot(void) const;
        std::string const               &getError(void) const;
        bool                            getIP_already_set(void) const;
        std::vector<std::string> const  &getIndex(void) const;

        std::string const   &get_cgi_ext(void) const;
        std::string const   &get_cgi_bin(void) const;



        void test(void);

bool operator==(const ServerConfig& other);


};

std::ostream& operator<<(std::ostream& os, const ServerConfig& config);

#endif
