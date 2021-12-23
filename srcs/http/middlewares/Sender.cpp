#include "Middleware.hpp"
#include <sstream>

Log& Sender::LOG = Log::getInstance();

Sender::Sender() {
}

void Sender::add_content_length(Response& response, std::ostringstream& oss) {
	std::map<std::string, std::string> const& headers
												= response.get_headers();
	std::map<std::string, std::string>::const_iterator it
										= headers.find("Content-Length");
	if (it == headers.end())
	{
		oss << response.get_body().length();
		response.set_header("Content-Length", oss.str()); 
		oss.str("");
	}
}

void Sender::write_all_on_write_buffer(ActiveHTTP& serv, Response& response,
		std::ostringstream& oss) {
	oss << response;
	serv.get_write_buffer() += oss.str();
	LOG.debug() << "Request totally written on the write buffer"<< std::endl;
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
	
	// If there is no ongoing task, set the response length to the length of
	// the body produced by the middlewares, and send the response
	if (!serv.get_delegation_to_task()) {
		add_content_length(response, oss);
		write_all_on_write_buffer(serv, response, oss);
		serv.reinitialize();
		return ;
	}
	// Otherwise, set the response as ready for the task to come
	response.ready();
}
