#ifndef MIDDLEWARE_HPP
# define MIDDLEWARE_HPP
# include <iostream>
# include "../Request/Request.hpp"
# include "../Response/Response.hpp"
# include "../../server/ActiveHTTP.hpp"

class MiddlewareChain;

class Middleware
{
	public:
		virtual ~Middleware() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain* next) = 0;
};

class CheckSyntax : public Middleware
{
	public:
		CheckSyntax();
		virtual	~CheckSyntax() {};
		void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain* next);
};

class BlockSelector : public Middleware
{
	public:
		BlockSelector();
		virtual	~BlockSelector() {};
		void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain* next);
};

class MethodChecker : public Middleware
{
	public:
		MethodChecker();
		virtual	~MethodChecker() {};
		void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain* next);
};
 
#endif
