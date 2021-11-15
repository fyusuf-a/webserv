#ifndef MIDDLEWARE_CHAIN_HPP
#define MIDDLEWARE_CHAIN_HPP

#include "Middleware.hpp"
#include <list>

class MiddlewareChain {
private:
	std::list<Middleware*> _chain;
	ActiveHTTP* _activeHTTP;
	Request _req;
	Response _resp;
	void _next();
	MiddlewareChain();

public:
	MiddlewareChain(ActiveHTTP* callback);
	~MiddlewareChain();
	MiddlewareChain(const MiddlewareChain&);
	MiddlewareChain& operator=(const MiddlewareChain& src);
	void operator()();
};

#endif
