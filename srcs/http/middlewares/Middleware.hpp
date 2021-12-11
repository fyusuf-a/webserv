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
# include "../../server/NIOSelector.hpp"


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

		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain&) = 0;
};

class CheckSyntax : public Middleware, public Singleton<CheckSyntax>
{
	public:
		CheckSyntax(){};
		virtual	~CheckSyntax() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain&);
};

class BlockSelector : public Middleware, public Singleton<BlockSelector>
{
	public:
		BlockSelector(){};
		virtual	~BlockSelector() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};

class MethodChecker : public Middleware, public Singleton<MethodChecker>
{
	public:
		MethodChecker(){};
		virtual	~MethodChecker() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain&);
};

class IndexSelector : public Middleware, public Singleton<IndexSelector>
{
	public:
		IndexSelector(){};
		virtual	~IndexSelector() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain&);
};

class MethodGET : public Middleware, public Singleton<MethodGET>
{
	public:
		MethodGET(){};
		virtual	~MethodGET() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain&);
};

class MethodDELETE : public Middleware, public Singleton<MethodDELETE>
{
	public:
		MethodDELETE(){};
		virtual	~MethodDELETE() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain&);
};

class MethodPOST : public Middleware, public Singleton<MethodPOST>
{
	public:
		MethodPOST(){};
		virtual	~MethodPOST() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain&);
};

class AbsolutePathConcatenator : public Middleware, public Singleton<AbsolutePathConcatenator>
{
	public:
		AbsolutePathConcatenator(){};
		virtual	~AbsolutePathConcatenator() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain&);
};

class Error : public Middleware, public Singleton<Error>
{
	public:
		Error(){};
		virtual	~Error() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain&);

};

class Sender : public Middleware, public Singleton<Sender>
{
	public:
		Sender(){};
		virtual	~Sender() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain&);
};
 



#endif
