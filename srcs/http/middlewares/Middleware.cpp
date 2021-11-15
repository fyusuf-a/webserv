#include "Middleware.hpp"
#include "MiddlewareChain.hpp"

MiddlewareChain::MiddlewareChain() {
}

MiddlewareChain::~MiddlewareChain() {
}

MiddlewareChain::MiddlewareChain(const MiddlewareChain& src) {
	if (this != &src)
	{
		operator=(
	}
}

void MiddlewareChain::_next() {
	if (_chain.empty())
		return ();
	_chain.pop_front();
}

void MiddlewareChain::operator()() {
	next();
}
