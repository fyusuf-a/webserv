#ifndef REQUEST_HPP
# define REQUEST_HPP
# include <iostream>
# include <map>
# include <list>
class Request
{
	private:
		std::string	_method;
		std::string _path;
		std::string _protocol;
		std::map<std::string, std::string>	_header;
		std::list<std::string>				_shadow_header;
		std::string _body;
		int			_head;
		bool		_over;
		std::string _residual;
		std::string	_field_name;
		std::size_t	_lctr;

	public:
		Request();
		Request(std::string& buffer);
		~Request();
		Request( Request const & src );
		Request & operator=( Request const & rhs );

		// Returns the index to which the parsing led
		void								parse(std::string& buffer);
		std::string							extract_attribute(std::string& buffer, std::string terminating);
		void								manage_head(std::string &buffer);
		void								deal_header_empty_line(std::string& buffer);
		void								checkIncompleteRequest(void) const;
		std::string							get_method(void) const;
		std::string							get_path(void) const;
		std::string							get_protocol(void) const;
		std::map<std::string, std::string>	get_header(void) const;
		std::string							get_body(void) const;
		std::string							get_residual(void) const;
		int									get_head(void) const;
		bool								get_over(void) const;
		void								set_over(bool over);
};

std::ostream& operator<<(std::ostream&, const Request&);

#endif
