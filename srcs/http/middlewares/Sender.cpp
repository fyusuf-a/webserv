#include "Middleware.hpp"

Sender::Sender() {
}

void Sender::body(ActiveHTTP&, Request& req, Response& resp, MiddlewareChain&) {
	std::cout << "----------------->" << req.get_location().get_location_path() << std::endl;
	resp.send();
}
