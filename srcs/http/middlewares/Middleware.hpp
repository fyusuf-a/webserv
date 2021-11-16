#ifndef MIDDLEWARE_HPP
# define MIDDLEWARE_HPP
# include <iostream>
# include "../Request/Request.hpp"
# include "../Response/Response.hpp"
# include "../../utils/Singleton.hpp"

class MiddlewareChain;
class ActiveHTTP;

class Middleware
{
	public:
		Middleware();
		Middleware(ActiveHTTP& callback);
		Middleware(const Middleware& src);
		virtual ~Middleware();
		Middleware& operator=(const Middleware& src);

		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next) = 0;
};

class CheckSyntax : public Middleware, public Singleton<CheckSyntax>
{
	public:
		CheckSyntax();
		virtual	~CheckSyntax() {};
		void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};

class BlockSelector : public Middleware, public Singleton<BlockSelector>
{
	public:
		BlockSelector();
		virtual	~BlockSelector() {};
		void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};

class MethodChecker : public Middleware, public Singleton<MethodChecker>
{
	public:
		MethodChecker();
		virtual	~MethodChecker() {};
		void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};

class AbsolutePathConcatenator : public Middleware, public Singleton<AbsolutePathConcatenator>
{
	public:
		AbsolutePathConcatenator();
		virtual	~AbsolutePathConcatenator() {};
		void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};

class Sender : public Middleware, public Singleton<Sender>
{
	public:
		Sender();
		virtual	~Sender() {};
		void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};
 
#endif
