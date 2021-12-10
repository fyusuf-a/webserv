#include "Middleware.hpp"
#include <sstream>

Sender::Sender() {
}

void Sender::body(ActiveHTTP& serv, Request&, Response& resp, MiddlewareChain& next) {
	std::ostringstream oss;

	// If there is no ongoing task, set the response length to the length of the body produced by the middlewares
	if (serv.get_ongoing_tasks().empty()) {
		std::map<std::string, std::string> const& headers = resp.get_headers();
		std::map<std::string, std::string>::const_iterator it = headers.find("Content-Length");
		if (it == headers.end())
		{
			oss << resp.get_body().length();
			resp.set_header("Content-Length", oss.str()); 
			oss.str("");
		}
	}

	// Give the server a name
	resp.set_header("Server", SERVER_NAME);

	// Send the date
	Utils::print_date(oss);
	resp.set_header("Date", oss.str());
	
	resp.ready();
	next();
}
