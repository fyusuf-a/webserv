#ifndef REQUEST_HPP
# define REQUEST_HPP
# include <iostream>
# include <map>

class Request
{
	private:
		std::string	_method;
		std::string _path;
		std::string _protocol;
		std::map<std::string, std::string> *_header;
		std::string _body;
		int			_head;
		int			_code;
		bool		_over;
		std::string _residual;

	public:
		Request();
		Request(char *str);
		~Request();
		Request( Request const & src );
		Request & operator=( Request const & rhs );

		char								*parse(char *str);
		std::string							extract_attribute(std::string req_copy, std::string terminating, char **ptr);
		void								check(void);
		int									check_header(void);
		std::string							get_method(void) const;
		std::string							get_path(void) const;
		std::string							get_protocol(void) const;
		std::map<std::string, std::string>	*get_header(void) const;
		std::string							get_body(void) const;
		int									get_head(void) const;
		int									get_code(void) const;
		bool								get_over(void) const;
		void								set_code(int code);
};

#endif