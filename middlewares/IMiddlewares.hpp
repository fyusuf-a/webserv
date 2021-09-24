#ifndef IMIDDLEWARES_HPP
# define IMIDDLEWARES_HPP
# include <iostream>

class IMiddlewares
{
	public:
		virtual ~IMiddlewares();
		void	body(void) = 0;
};

#endif