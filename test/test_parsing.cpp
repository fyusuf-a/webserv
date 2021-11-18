#include "../srcs/parsingConf/parsingConf.hpp"
#include "../srcs/parsingConf/serverBlock.hpp"

#define DEFAULT_PATH "../conf/is_good.conf"
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



#define SERVER_PORT 500
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1


void init(const std::string& path, ServerBlocks& servers) {
	ParsingConf conf;
    conf.parsing(path, servers);
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
                throw MyException("[ERROR] File: Can't open File !");

            init(DEFAULT_PATH, server_blocks1);

            fd << server_blocks1;

            init(av[1], server_blocks2);

			std::cout << server_blocks2;
        }
    }

    catch(MyException& caught)
    {
        std::cout << "[ERROR] " << caught.what() << std::endl;
        return (1);

    }

    try
    {
        init(ERROR1, server_blocks1);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        init(ERROR2, server_blocks1);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        init(ERROR3, server_blocks1);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        init(ERROR4, server_blocks1);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        init(ERROR5, server_blocks1);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        init(ERROR6, server_blocks1);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        init(ERROR7, server_blocks1);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        init(ERROR8, server_blocks1);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        init(ERROR9, server_blocks1);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        init(ERROR10, server_blocks1);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        init(ERROR11, server_blocks1);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
  return (value);
}
