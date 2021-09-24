#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <libc.h>
#include <iostream>
#include "config.hpp"
#include "server.hpp"



class WebServ
{

    private:
        Config       _conf;
        Servers      _servers;

    public:
        WebServ();

        WebServ(const WebServ &other);

        ~WebServ();

        WebServ &operator=(const WebServ &other);

        void init(std::string path);



};


#endif
