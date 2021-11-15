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

class MethodsCheker : public Middleware
{
	public:
		virtual	~MethodsCheker() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, Middleware* next);
};



#endif
