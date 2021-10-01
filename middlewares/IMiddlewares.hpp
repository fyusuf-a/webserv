#ifndef IMIDDLEWARES_HPP
# define IMIDDLEWARES_HPP
# include <iostream>
# include "config.hpp"
# include "Request.hpp"
class IMiddlewares
{
	public:
		virtual ~IMiddlewares();
		void	body(Config & config, Request & resquest, IMiddlewares *next) = 0;
};

#endif