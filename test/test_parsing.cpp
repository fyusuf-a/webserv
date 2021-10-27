#include "../includes/webserv.hpp"
#define DEFAULT_PATH "../conf/is_good.conf"
#define SERVER_PORT 500
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1



int main(int ac, char **av)
{

    WebServ webserv1;
    WebServ webserv2;

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
  return (0);
}