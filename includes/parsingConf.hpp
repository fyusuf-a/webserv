#ifndef PARSINGCONF_HPP
#define PARSINGCONF_HPP
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "utils.hpp"
#include "serverBlock.hpp"

#define ITER std::vector<std::string>::iterator
#define ServerBlocks std::vector<ServerBlock>

class ParsingConf
{
    public:
        
        ParsingConf();
        ParsingConf(const ParsingConf &other);
        ~ParsingConf();

        ParsingConf &operator=(const ParsingConf &other);



        bool    is_location_block(std::string const &line);
        bool    is_serv_block(std::string const &line);

        void    setup_location_directive(std::string const &line, ServerLocation &location);
        void    setup_server_directive(std::string const &line, ServerBlock &server);

        void    setup_location(ITER &start, ITER &end, ServerBlock &server, std::string test);
        void    setup_server(ITER &start, ITER &end, ServerBlocks &servers);

        void    setup_servers(std::vector<std::string> &content, ServerBlocks &servers);


        int     parse_directive(std::string const &line, std::string &directive);
        bool    parse_value(std::string const &line, std::string &value, int i);


        std::vector<std::string>    parsing_index_value(std::string val);
        std::vector<std::string>    parsing_methods_value(std::string val, std::string dir);
        std::string                 parsing_path_value(std::string val, std::string dir);
        std::string                 parsing_cgi_ext_value(std::string val, std::string dir);
        std::string                 parsing_name_value(std::string val, std::string dir);
        std::string                 parsing_location_path(std::string val);
        std::string                 parsing_host_value(std::string val, std::string dir);
        uint16_t                    parsing_port_value(std::string val, std::string dir);
        size_t                      parsing_body_size_value(std::string val, std::string dir);
        int                         parsing_bool_value(std::string val, std::string dir);

        void                         parsing(std::string path, ServerBlocks &servers);
        std::vector<std::string>     parsing_line(std::string line, std::vector<std::string> content);
};

#endif
