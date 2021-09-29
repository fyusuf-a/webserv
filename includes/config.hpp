#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "utils.hpp"
#include "server.hpp"

#define ITER std::vector<std::string>::iterator
#define Servers std::vector<Server>

class Config
{
    private:


    public:
        Config();
        Config(const Config &other);
        ~Config();
        Config &operator=(const Config &other);

        bool    is_location_block(std::string const &line);
        bool    is_serv_block(std::string const &line);
        int     parsing(std::string path, Servers &servers);
        void    setup_servers(std::vector<std::string> &content, Servers &servers);
        void    setup_server(ITER &start, ITER &end, Servers &servers);
        void    setup_location(ITER &start, ITER &end);
        void    setup_others(std::string const &start, Server &server);

        int     parse_directive(std::string const &line, std::string &directive);
        bool    parse_value(std::string const &line, std::string &value, int i);

        std::vector<std::string> parsing_line(std::string line, std::vector<std::string> content);
};


#endif
