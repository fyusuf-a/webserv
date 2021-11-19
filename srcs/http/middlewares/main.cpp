#include "../../ipaddress/IPAddress.hpp"
#include "../../ipaddress/INetAddress.hpp"
#include "../../parsingConf/parsingConf.hpp"
#include "../../server/ActiveHTTP.hpp"
#include "MiddlewareChain.hpp"
#include <vector>

int launch_the_test(std::string path, std::string reqstr) {
	IPAddress  adr(0);
	INetAddress iadr(adr, 8001);
	ParsingConf conf;
	ServerBlocks sb;
	Socket *sock = new Socket;
	Request req;
	Response resp;

	conf.parsing(path, sb);
	ActiveHTTP actHTTP(sock, iadr, &sb);

	while (req.get_head() < 6)
		req.parse(reqstr);

	MiddlewareChain chn(&actHTTP, &req, &resp);
	chn();
	std::cout << req << "/////////" << std::endl << resp << std::endl;
	return (0);
}

int main()
{
	launch_the_test("conf/is_good.conf", "GET /Makefile HTTP/1.1\r\nHost:test\r\n\r\n");

	#ifdef CS_FLAG
		launch_the_test("conf/is_good.conf", "GET / HTTP/11\r\nHost:test\r\n\r\n");
		launch_the_test("conf/is_good.conf", "GET / HTTP/1.1\r\nHost:test\r\nHost:test2\r\n\r\n");
		launch_the_test("conf/is_good.conf", "GETR / HTTP/1.1\r\nHost:test\r\n\r\n");
		launch_the_test("conf/is_good.conf", "GET oui/ HTTP/1.1\r\nHost:test\r\n\r\n");
		launch_the_test("conf/is_good.conf", "GET / HTTP/1.1\r\nHost    :test\r\n\r\n");
		launch_the_test("conf/is_good.conf", "GET / HTTP/1.1\r\nHost:     test\r\n\r\n");
	#endif
 	return (0);
}
