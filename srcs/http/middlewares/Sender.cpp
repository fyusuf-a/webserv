#include "Middleware.hpp"

Sender::Sender() {
}

void Sender::body(ActiveHTTP& serv, Request&, Response& resp, MiddlewareChain& next) {
	// If there is no ongoing task, set the response length to the length of the body produced by the middlewares
	if (!serv.get_ongoing_task()) {
		std::map<std::string, std::string> const& headers = resp.get_headers();
		std::map<std::string, std::string>::const_iterator it = headers.find("Content-Length");
		if (it == headers.end())
		{
			std::ostringstream os;
			os << resp.get_body().length();
			resp.set_header("Content-Length", os.str()); 
		}
	}

	// Give the server a name
	resp.set_header("Server", SERVER_NAME);
	
	resp.ready();
	next();
}
