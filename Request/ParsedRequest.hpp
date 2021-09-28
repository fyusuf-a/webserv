#ifndef PARSEDREQUEST_HPP
# define PARSEDREQUEST_HPP
# include <iostream>
# include <map>

class ParsedRequest
{
	private:
		std::string	_method;
		std::string _path;
		std::string _protocol;
		std::map<std::string, std::string> _header;
		std::map<std::string, std::string> _body;
		int			_head;

	public:
		ParsedRequest();
		~ParsedRequest();
		ParsedRequest( ParsedRequest const & src );
		ParsedRequest & operator=( ParsedRequest const & rhs );

		char								*parse(char *c);
		std::string							get_method(void) const;
		std::string							get_path(void) const;
		std::string							get_protocol(void) const;
		std::map<std::string, std::string>	get_header(void) const;
		std::map<std::string, std::string>	get_body(void) const;
		int									get_head(void) const;
};

#endif