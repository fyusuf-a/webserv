#ifndef MIDDLEWARES_HPP
# define MIDDLEWARES_HPP
# include <iostream>
# include "Request.hpp"

class IMiddlewares
{
	public:
		virtual ~IMiddlewares() {};
		virtual void	body(Request & resquest) = 0;
};

class CheckSyntax : public IMiddlewares
{
	public:
		virtual	~CheckSyntax() {};
		void	body(Request & resquest);
};

#endif