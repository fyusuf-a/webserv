#ifndef MIDDLEWARE_CHAIN_HPP
#define MIDDLEWARE_CHAIN_HPP

#include "Middleware.hpp"
#include <list>

class Middleware;

class MiddlewareChain {
private:
	void init();
	std::list<Middleware*> _chain;
	ActiveHTTP* _activeHTTP;
	Request* _req;
	Response* _resp;

	void _next();
	MiddlewareChain();

public:
	MiddlewareChain(ActiveHTTP* callback, Request* _req, Response* _resp);
	~MiddlewareChain();
	MiddlewareChain(const MiddlewareChain&);
	MiddlewareChain& operator=(const MiddlewareChain& src);
	void operator()();
};

#endif
