#include "Middleware.hpp"

Middleware::Middleware() {
}

Middleware::~Middleware() {
}

Middleware::Middleware(const Middleware& src) {
	*this = src;
}

Middleware& Middleware::operator=(const Middleware&) {
	return (*this);
}
