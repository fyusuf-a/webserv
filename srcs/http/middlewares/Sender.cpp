#include "Middleware.hpp"

Sender::Sender() {
}

void Sender::body(ActiveHTTP&, Request&, Response& resp, MiddlewareChain&) {
	resp.send();
}
