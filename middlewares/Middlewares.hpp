#ifndef MIDDLEWARES_HPP
# define MIDDLEWARES_HPP
# include <iostream>
# include "config.hpp"
# include "Request.hpp"

class IMiddlewares
{
	public:
		virtual ~IMiddlewares();
		void	body(Config & config, Request & resquest, IMiddlewares *next) = 0;
};

class CheckSyntax : public IMiddlewares
{
	public:
		virtual	~CheckSyntax();
		void	body(Config & config, Request & resquest, IMiddlewares *next);
};

#endif