#include "MiddlewareChain.hpp"
#include "Middleware.hpp"

MiddlewareChain::MiddlewareChain() {
	CheckSyntax check_syntax = CheckSyntax();
	_chain.push_back(&check_syntax);
}

MiddlewareChain::MiddlewareChain(const MiddlewareChain& src) {
	*this = src;
}

MiddlewareChain& MiddlewareChain::operator=(const MiddlewareChain& src) {
	if (this != &src) {
		_chain = src._chain;
	}
	return (*this);
}

MiddlewareChain::~MiddlewareChain() {
}

void MiddlewareChain::_next() {
	if (_chain.empty())
		return;
	Middleware* middleware = _chain.front();
	_chain.pop_front();
	middleware->body(_req, _resp, this);
}



void MiddlewareChain::operator()() {
	_next();
}
