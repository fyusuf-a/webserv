#ifndef WEBSERV_HPP
#define WEBSERV_HPP
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../parsingConf/parsingConf.hpp"
#include "../parsingConf/serverBlock.hpp"


#define ServerBlocks std::vector<ServerBlock>

class WebServ
{

    public:
        ParsingConf   _conf;
        ServerBlocks  _servers;
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
