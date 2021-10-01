#ifndef REQUEST_HPP
# define REQUEST_HPP
# include <iostream>
# include "ParsedRequest.hpp"

class Request
{
	private:
		ParsedRequest	_fields;
		int				_code;
	public:
		Request();
		Request( ParsedRequest req );
		Request( Request const & src );
		~Request();
		Request & operator=( Request const & rhs );

		ParsedRequest	get_fields(void) const;
		int				get_code(void) const;
		void			check(void);
		int				check_header(void);
};

#endif