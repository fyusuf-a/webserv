#include "Middleware.hpp"
#include <sstream>

Log& Sender::LOG = Log::getInstance();

Sender::Sender() {
}

void Sender::body(ActiveHTTP& serv, Request& request, Response& response, MiddlewareChain&) {

	// If the client wants to close the connection, grant its wish
	try {
		if (request.get_headers().at("Connection") == "close")
			response.set_header("Connection", "close");
	}
	catch (std::out_of_range& e) {
	}

	// Give the server a name
	response.set_header("Server", SERVER_NAME);

	// Send the date
	std::ostringstream oss;
	Utils::print_date(oss);
	response.set_header("Date", oss.str());
	oss.str("");
	
	// If ther is an ongoing task, set the response as ready for the task to come
	if (serv.get_delegation_to_task())
		response.ready();
}
