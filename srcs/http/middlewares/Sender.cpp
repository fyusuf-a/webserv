#include "Middleware.hpp"

Sender::Sender() {
}

void Sender::body(ActiveHTTP& serv, Request&, Response& resp, MiddlewareChain& next) {
	if (!serv.get_ongoing_task()) {
		std::map<std::string, std::string> const& my_map = resp.get_headers();
		std::map<std::string, std::string>::const_iterator it = my_map.find("Content-Length");
		// Deleting the active server if a Connection: close is found
		if (it == my_map.end())
		{
			std::ostringstream os;
			os << resp.get_body().length();
			resp.set_header("Content-Length", os.str()); 
		}
	}
	//std::cout << resp.get_body()<<std::endl;;
	resp.ready();
	next();
}
