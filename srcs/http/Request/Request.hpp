#ifndef REQUEST_HPP
# define REQUEST_HPP
# include <iostream>
# include <map>
#include <ostream>

class Request
{
	private:
		std::string		_method;
		std::string 	_path;
		std::string 	_protocol;
		std::map<std::string, std::string> *_header;
		std::string 	_body;
		int				_head;
		bool			_over;
		std::string 	_residual;
		std::string		_field_name;

	public:
		Request();
		Request(std::string& str);
		~Request();
		Request( Request const & src );
		Request & operator=( Request const & rhs );

		std::string&						parse(std::string&);
		void								parse_all(std::string&);
		std::string							extract_attribute(std::string req_copy, std::string terminating, std::string& str, std::size_t residual_offset);
		void								manage_head(std::string&);
		void								checkIncompleteRequest(void) const;
		std::string							get_method(void) const;
		std::string							get_path(void) const;
		std::string							get_protocol(void) const;
		std::map<std::string, std::string>	*get_header(void) const;
		std::string							get_body(void) const;
		std::string							get_residual(void) const;
		int									get_head(void) const;
		bool								get_over(void) const;
		void								set_over(bool over);
};

std::ostream& operator<<(std::ostream&, const Request&);

#endif
