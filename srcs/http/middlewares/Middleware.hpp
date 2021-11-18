#ifndef MIDDLEWARE_HPP
# define MIDDLEWARE_HPP
# include <iostream>
# include "../Request/Request.hpp"
# include "../Response/Response.hpp"
# include "../../utils/Singleton.hpp"
# include "../../webserv/webserv.hpp"
# include "../../ipaddress/INetAddress.hpp"
# include "MiddlewareChain.hpp"
# include "../../server/ActiveHTTP.hpp"

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
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};

class BlockSelector : public Middleware, public Singleton<BlockSelector>
{
	public:
		BlockSelector();
		virtual	~BlockSelector() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};

class MethodChecker : public Middleware, public Singleton<MethodChecker>
{
	public:
		MethodChecker();
		virtual	~MethodChecker() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};

class IndexSelector : public Middleware, public Singleton<IndexSelector>
{
	public:
		IndexSelector(){};
		virtual	~IndexSelector() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};

class MethodGET : public Middleware, public Singleton<MethodGET>
{
	public:
		MethodGET(){};
		virtual	~MethodGET() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};

class MethodDELETE : public Middleware, public Singleton<MethodGET>
{
	public:
		MethodDELETE(){};
		virtual	~MethodDELETE() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};

class AbsolutePathConcatenator : public Middleware, public Singleton<AbsolutePathConcatenator>
{
	public:
		AbsolutePathConcatenator();
		virtual	~AbsolutePathConcatenator() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};

class Sender : public Middleware, public Singleton<Sender>
{
	public:
		Sender();
		virtual	~Sender() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};
 



#endif
