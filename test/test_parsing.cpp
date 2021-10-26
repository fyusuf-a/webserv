#include "includes/webserv.hpp"
#define DEFAULT_PATH "conf/nginx.conf"
#define SERVER_PORT 500
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1



int main(int ac, char **av)
{

    WebServ webserv;

    try 
    {
        if (ac == 2)
            webserv.init(av[1]);
        else
            webserv.init(DEFAULT_PATH);
    }

    catch(MyException& caught)
    {
        std::cout << "[ERROR] " << caught.what() << std::endl;
        return (1);

    }
  return (0);
}