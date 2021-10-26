#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "parsingConf.hpp"
#include "serverBlock.hpp"



class WebServ
{

    public:
        ParsingConf  _conf;
        ServerBlocks      _servers;
        void init(const std::string& path);

    public:
        WebServ();
        WebServ(const WebServ &other);
        WebServ(const std::string& path);
        ~WebServ();
        WebServ &operator=(const WebServ &other);
		ServerBlocks const& get_servers() const;




};

std::ostream& operator<<(std::ostream& os, const WebServ& webserv);

#endif
