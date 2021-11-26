#include "Middleware.hpp"

Sender::Sender() {
}

void Sender::body(ActiveHTTP&, Request&, Response& resp, MiddlewareChain&) {
	std::cout << resp.get_body()<<std::endl;;
	resp.ready();
}
