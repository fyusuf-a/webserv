#include "srcs/ipaddress/IPAddress.hpp"
#include "srcs/webserv/webserv.hpp"
#include "srcs/server/NIOSelector.hpp"
#include "srcs/utils/Log.hpp"
#define DEFAULT_PATH "conf/is_good.conf"
#define SERVER_PORT 500
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

Log& LOG = Log::getInstance();

int main(int ac, char **av)
{
	std::string path = ac == 2 ? av[1] : DEFAULT_PATH;

#ifdef DEBUG_FLAG
	LOG.setLevel(DEBUG);
#else
	LOG.setLevel(DEBUG);
#endif
	try
    {
 		WebServ* webserv = new WebServ(path);
		while (1)
			NIOSelector::getInstance().poll();
		delete webserv;
    }
    catch(MyException& caught)
    {
        LOG.error() << caught.what() << std::endl;
        exit(EXIT_FAILURE) ;
    }
	catch(std::invalid_argument& caught) 
    {
		LOG.error() << caught.what() << std::endl;
		exit(EXIT_FAILURE);
	}
 	return (0);
}
