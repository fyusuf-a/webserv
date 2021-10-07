#ifndef PARSINGCONF_HPP
#define PARSINGCONF_HPP
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "utils.hpp"
#include "server.hpp"

#define ITER std::vector<std::string>::iterator
#define Servers std::vector<Server>

class ParsingConf
{
    private:


    public:
        ParsingConf();
        ParsingConf(const ParsingConf &other);
        ~ParsingConf();
        ParsingConf &operator=(const ParsingConf &other);



        bool    is_location_block(std::string const &line);
        bool    is_serv_block(std::string const &line);
        int     parsing(std::string path, Servers &servers);
        void    setup_servers(std::vector<std::string> &content, Servers &servers);
        void    setup_server(ITER &start, ITER &end, Servers &servers);
        void    setup_location(ITER &start, ITER &end, Server &server);
        void    setup_location_directive(std::string const &line, ServerLocation &location);
        void    setup_server_directive(std::string const &start, Server &server);
        int     parse_directive(std::string const &line, std::string &directive);
        bool    parse_value(std::string const &line, std::string &value, int i);


        std::vector<std::string> parsing_index_value(std::string val);
        std::vector<std::string> parsing_methods_value(std::string val, std::string dir);
        std::string parsing_bool_value(std::string val, std::string dir);
        std::string parsing_path_value(std::string val, std::string dir);
        std::string parsing_cgi_ext_value(std::string val, std::string dir);
        std::string parsing_name_value(std::string val, std::string dir);
        uint32_t    parsing_host_value(std::string val, std::string dir);
        int         parsing_digit_value(std::string val, std::string dir);






        std::vector<std::string> parsing_line(std::string line, std::vector<std::string> content);
};

#endif