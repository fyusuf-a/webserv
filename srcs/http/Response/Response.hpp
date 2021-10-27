#ifndef RESPONSE_HPP
# define RESPONSE_HPP
# include <iostream>

class Response
{
	private:
		int	_code;
	public:
		Response();
		~Response();
		Response( Response const & src );
		Response & operator=( Response const & rhs );

		int		get_code(void) const;
		void	set_code(int code);
};

#endif