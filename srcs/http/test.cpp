#include <list>
#include "../utils/Log.hpp"
#include "middlewares/Middlewares.hpp"
#include "Response/Response.hpp"
#define DEFAULT_PATH "../../conf/is_good.conf"
#define SERVER_PORT 500
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1


Log& LOG = Log::getInstance();

class Response;


void	req_check_syntax(std::string str, WebServ &webserv) {

	IPAddress  adr(0);
	INetAddress iadr(adr, 80);
	Request		req;
	Response 	resp;

	std::list<IMiddlewares *> middlewares;
	std::list<IMiddlewares *>::iterator it;
	std::map<std::string, std::string>::iterator it2;
	
	CheckSyntax		csx;
	BlockSelector	bs;
	MethodsCheker  mc;

	// while (1) {
	// 	if (!_still_parsing)
	// 		_reqs.resize(_reqs.size() + 1);
	// 	_reqs.back().set_over(true);
	// 	while (_reqs.back().get_head() < 6 && _reqs.back().get_over()) {
	// 		_reqs.back().parse(_read_buffer);
	// 	}
	// 	_still_parsing = _reqs.back().get_over() == 0 ? 1 : 0;
	// 	if (_read_buffer == "" || !_reqs.back().get_over())
	// 		break ;
	// }
	while (req.get_head() < 6 && req.get_over() == true)
		req.parse(str);

	
	middlewares.push_back(&csx);
	middlewares.push_back(&bs);
	middlewares.push_back(&mc);


	
	try {
		for (it = middlewares.begin(); it != middlewares.end(); ++it) {
			(*it)->body(req, resp, webserv._servers, iadr);
		}
	}
	catch (Response::http_code code) {
		resp.set_code(code);
	}
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
		
		req_check_syntax("GET /test HTTP/1.1\r\nHost: test\r\n\r\n", webserv);

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
