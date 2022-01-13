#ifndef PARSINGCONF_HPP
#define PARSINGCONF_HPP
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "../utils/utils.hpp"
#include "../parsingConf/serverBlock.hpp"

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

        void    setup_location(ITER &start, ITER &end, ServerBlock &server, const std::string& test);
        void    setup_server(ITER &start, ITER &end, ServerBlocks &servers);

        void    setup_servers(std::vector<std::string> &content, ServerBlocks &servers);


        int     parse_directive(const std::string&, std::string &directive);
        bool    parse_value(std::string const &line, std::string &value, int i);


        std::vector<std::string>    parsing_index_value(const std::string&);
        std::vector<std::string>    parsing_methods_value(const std::string&, const std::string& dir);
        std::string                 parsing_path_value(std::string, const std::string& dir);
        std::string                 parsing_cgi_ext_value(std::string);
        std::string                 parsing_name_value(const std::string&, const std::string& dir);
        std::string                 parsing_location_path(const std::string&);
        std::string                 parsing_host_value(const std::string&, const std::string& dir);
        uint16_t                    parsing_port_value(const std::string&, const std::string& dir);
        size_t                      parsing_body_size_value(const std::string&, const std::string& dir);
        int                         parsing_bool_value(std::string, const std::string& dir);

        void                         parsing(const std::string& path, ServerBlocks &servers);
        std::vector<std::string>     parsing_line(std::string, std::vector<std::string> content);
};

#endif
