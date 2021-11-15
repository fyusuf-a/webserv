#ifndef MIDDLEWARES_HPP
# define MIDDLEWARES_HPP
# include <iostream>
# include "../Request/Request.hpp"
# include "../Response/Response.hpp"
# include "../../webserv/webserv.hpp"
# include "../../ipaddress/INetAddress.hpp"
# include "../../server/ActiveHTTP.hpp"


class Middleware
{
	public:
		virtual ~Middleware() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, Middleware* next) = 0;
};

class CheckSyntax : public Middleware
{
	public:
		virtual	~CheckSyntax() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, Middleware* next);

};

class BlockSelector : public Middleware
{
	public:
		virtual	~BlockSelector() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, Middleware* next);

};

class MethodChecker : public Middleware
{
	public:
		virtual	~MethodChecker() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, Middleware* next);
};

class IndexSelector : public Middleware
{
	public:
		virtual	~IndexSelector() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, Middleware* next);
};

#endif
