#include "../srcs/parsingConf/parsingConf.hpp"
#include "../srcs/parsingConf/serverBlock.hpp"
#include <stdexcept>

#define DEFAULT_PATH "../conf/config.conf"
#define ERROR1  "./tests_conf/is_not1.conf"
#define ERROR2  "./tests_conf/is_not2.conf"
#define ERROR3  "./tests_conf/is_not3.conf"
#define ERROR4  "./tests_conf/is_not4.conf"
#define ERROR5  "./tests_conf/is_not5.conf"
#define ERROR6  "./tests_conf/is_not6.conf"
#define ERROR7  "./tests_conf/is_not7.conf"
#define ERROR8  "./tests_conf/is_not8.conf"
#define ERROR9  "./tests_conf/is_not9.conf"
#define ERROR10 "./tests_conf/is_not10.conf"
#define ERROR11 "./tests_conf/is_not11.conf"

#include <iostream>

#define SERVER_PORT 500
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

void init(const std::string& path, ServerBlocks& servers) {
	ParsingConf conf;
    conf.parsing(path, servers);
}

void init_should_fail(const std::string& path, ServerBlocks& servers) {
	init(path, servers);
	std::cerr << "[ERROR] loaded file " << path << " sucessfully" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const ServerBlocks& servers) {
	for(std::vector<ServerBlock>::const_iterator i = servers.begin()
			;i != servers.end(); i++) {
		os << *i;
	}
    return os;
}

int main(int ac, char **av)
{

	ServerBlocks server_blocks1;
	ServerBlocks server_blocks2;
    int     value = 0;

    try 
    {
        if (ac == 2)
        {
            std::fstream               fd(av[1]);


            if (!fd.is_open() && !fd.good())
                throw std::runtime_error("File: Can't open file");
            init(DEFAULT_PATH, server_blocks1);

            fd << server_blocks1;

            init(av[1], server_blocks2);

			std::cout << server_blocks2;
        }
    }
    catch(std::runtime_error& caught)
    {
        std::cerr << "[ERROR] " << caught.what() << " \""
			<< std::string(av[1]) + "\"" << std::endl;
        return (1);

    }

    try
    {
        init_should_fail(ERROR1, server_blocks1);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        init_should_fail(ERROR2, server_blocks1);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        init_should_fail(ERROR3, server_blocks1);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        init_should_fail(ERROR4, server_blocks1);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        init_should_fail(ERROR5, server_blocks1);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        init_should_fail(ERROR6, server_blocks1);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        init_should_fail(ERROR7, server_blocks1);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        init_should_fail(ERROR8, server_blocks1);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        init_should_fail(ERROR9, server_blocks1);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        init_should_fail(ERROR10, server_blocks1);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        init_should_fail(ERROR11, server_blocks1);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
	return (value);
}
