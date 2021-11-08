#ifndef MIDDLEWARES_HPP
# define MIDDLEWARES_HPP
# include <iostream>
# include "../Request/Request.hpp"
# include "../Response/Response.hpp"
# include "../../webserv/webserv.hpp"
# include "../../ipaddress/INetAddress.hpp"


class IMiddlewares
{
	public:
		virtual ~IMiddlewares() {};
		// virtual void	body(Request & resquest, Response & response) = 0;

		virtual void	body(Request & request, Response & response, ServerBlocks const &serverBlocks, INetAddress const* interface) = 0;
};

class CheckSyntax : public IMiddlewares
{
	public:
		virtual	~CheckSyntax() {};
		// void	body(Request & resquest, Response & response);
		virtual void	body(Request & request, Response & response, ServerBlocks const &serverBlocks, INetAddress const* interface);

};

class BlockSelector : public IMiddlewares
{
	public:
		virtual	~BlockSelector() {};
		// void	body(Request & resquest, Response & response);
		virtual void	body(Request & request, Response & response, ServerBlocks const &serverBlocks, INetAddress const* interface);

};



#endif
