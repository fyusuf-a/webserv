#include "srcs/ipaddress/IPAddress.hpp"
#include "srcs/webserv/webserv.hpp"
#include "srcs/server/NIOSelector.hpp"
#define DEFAULT_PATH "conf/is_good.conf"
#define SERVER_PORT 500
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1



int main(int ac, char **av)
{
	std::string path = ac == 2 ? av[1] : DEFAULT_PATH;

	try
    {
 		WebServ webserv(path);
 	    //std::cout << webserv;
    }
    catch(MyException& caught)
    {
        std::cout << "[ERROR] " << caught.what() << std::endl;
        exit(EXIT_FAILURE) ;
    }
	catch(std::invalid_argument& caught) 
    {
		std::cout << "[ERROR] " << caught.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	while (1) {
	 	NIOSelector::getInstance()->poll();
	}

 	return (0);
}
