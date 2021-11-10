#include <list>
#include "../utils/Log.hpp"
#include "middlewares/Middlewares.hpp"
#define DEFAULT_PATH "../../conf/is_good.conf"
#define SERVER_PORT 500
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1


Log& LOG = Log::getInstance();


void	req_check_syntax(char const *str, WebServ &webserv) {

	IPAddress  adr(1);
	INetAddress iadr(adr, 80);
	Request		req;
	Response 	resp;
	std::list<IMiddlewares *> middlewares;
	std::list<IMiddlewares *>::iterator it;
	std::map<std::string, std::string>::iterator it2;
	
	CheckSyntax		csx;
	BlockSelector	bs;

	while (req.get_head() < 6 && req.get_over() == true)
		str = req.parse(str);

	
	middlewares.push_back(&csx);
	middlewares.push_back(&bs);

	
	try {
		for (it = middlewares.begin(); it != middlewares.end(); ++it) {
			(*it)->body(req, resp, webserv._servers, iadr);
		}
	}
	catch (int code) {resp.set_code(code);}
	std::cout << resp.get_code() << std::endl;
}


int	main(int ac, char **av) {

	std::string path = ac == 2 ? av[1] : DEFAULT_PATH;

	#ifdef DEBUG_FLAG
		LOG.setLevel(DEBUG);
	#else
		LOG.setLevel(INFO);
	#endif

	try
    {
 		WebServ webserv(path);
		
		req_check_syntax((char *)"GET           /req.html HTTP/1.1\r\nHost: test\r\nContent-Length: non\r\n\r\nrereq: ah\r\n\r\n", webserv);

 	    //std::cout << webserv;
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


}
