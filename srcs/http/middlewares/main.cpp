#include "../../ipaddress/IPAddress.hpp"
#include "../../ipaddress/INetAddress.hpp"
#include "../../parsingConf/parsingConf.hpp"
#include "../../server/ActiveHTTP.hpp"
#include "MiddlewareChain.hpp"
#include <vector>

int launch_the_test(std::string path, std::string reqstr, int supposed_response_code) {
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
	std::cout << req << resp << std::endl;
	return (resp.get_code() != supposed_response_code);
}

int main()
{
	launch_the_test("conf/is_good.conf", "GET /InstallHistory.plist HTTP/1.1\r\nHost:test\r\n\r\n", 200);

	#ifdef CS_FLAG
		if ( launch_the_test("conf/is_good.conf", "GET / HTTP/11\r\nHost:test\r\n\r\n", 505) ||
			launch_the_test("conf/is_good.conf", "GET / HTTP/1.1\r\nHost:test\r\nHost:test2\r\n\r\n", 200) ||
			launch_the_test("conf/is_good.conf", "GETR / HTTP/1.1\r\nHost:test\r\n\r\n", 501) ||
			launch_the_test("conf/is_good.conf", "GET oui/ HTTP/1.1\r\nHost:test\r\n\r\n", 400) ||
			launch_the_test("conf/is_good.conf", "GET / HTTP/1.1\r\n   Host:test\r\n\r\n", 400) ||
			launch_the_test("conf/is_good.conf", "GET / HTTP/1.1\r\nfdshj fs   Host:test\r\n\r\n", 400) ||
			launch_the_test("conf/is_good.conf", "GET / HTTP/1.1\r\nHost:     test\r\n\r\n", 200))
			return (1);
	#endif
	#ifdef APC_FLAG
		if ( launch_the_test("conf/apcconf1.conf", "GET /AppendToPath HTTP/1.1\r\nHost:test\r\n\r\n", 200) ||
			launch_the_test("conf/apcconf1.conf", "GET /Printers/ HTTP/1.1\r\nHost:test\r\n\r\n", 200) ||
			launch_the_test("conf/apcconf2.conf", "GET / HTTP/1.1\r\nHost:test\r\n\r\n", 200) || 
			launch_the_test("conf/apcconf1.conf", "GET /MunkiReport/Logs/errors.log HTTP/1.1\r\nHost:test\r\n\r\n", 405))
			return (1);
	#endif
	#ifdef IS_FLAG
		if ( launch_the_test("conf/index_selector.conf", "GET / HTTP/1.1\r\nHost:test\r\n\r\n", 200) ||
			launch_the_test("conf/index_selector.conf", "GET /manual/ HTTP/1.1\r\nHost:test\r\n\r\n", 200) ||
			launch_the_test("conf/index_selector.conf", "GET /images/ HTTP/1.1\r\nHost:test\r\n\r\n", 200)||
			launch_the_test("conf/index_selector.conf", "GET /manual HTTP/1.1\r\nHost:test\r\n\r\n", 200))
			return (1);
	#endif
 	return (0);
}
