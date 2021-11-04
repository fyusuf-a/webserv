#include "../srcs/webserv/webserv.hpp"

#define DEFAULT_PATH "../conf/is_good.conf"
#define ERROR1 "./tests_conf/is_not1.conf"
#define ERROR2 "./tests_conf/is_not2.conf"
#define ERROR3 "./tests_conf/is_not3.conf"
#define ERROR4 "./tests_conf/is_not4.conf"
#define ERROR5 "./tests_conf/is_not5.conf"
#define ERROR6 "./tests_conf/is_not6.conf"
#define ERROR7 "./tests_conf/is_not7.conf"
#define ERROR8 "./tests_conf/is_not8.conf"
#define ERROR9 "./tests_conf/is_not9.conf"


#define SERVER_PORT 500
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1



int main(int ac, char **av)
{

    WebServ webserv1;
    WebServ webserv2;
    int     value = 0;

    try 
    {
        if (ac == 2)
        {
            std::fstream               fd(av[1]);


            if (!fd.is_open() && !fd.good())
                throw MyException("[ERROR] File: Can't open File !");

            webserv1.init(DEFAULT_PATH);

            fd << webserv1;

            webserv2.init(av[1]);

			std::cout << webserv2;
        }
    }

    catch(MyException& caught)
    {
        std::cout << "[ERROR] " << caught.what() << std::endl;
        return (1);

    }

    try
    {
        webserv1.init(ERROR1);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        webserv1.init(ERROR2);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        webserv1.init(ERROR3);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        webserv1.init(ERROR4);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        webserv1.init(ERROR5);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        webserv1.init(ERROR6);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        webserv1.init(ERROR7);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        webserv1.init(ERROR8);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
    try
    {
        webserv1.init(ERROR9);
    }
    catch(MyException& caught)
    {
        value += 1;
    }
  return (value);
}
