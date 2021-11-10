#ifndef REQUEST_HPP
# define REQUEST_HPP
# include <iostream>
# include <map>
# include "../../parsingConf/serverBlock.hpp"

class ServerBlock;

class Request
{
	private:
		std::string	_method;
		std::string _path;
		std::string _protocol;
		std::map<std::string, std::string> *_header;
		std::string _body;
		int			_head;
		bool		_over;
		std::string _residual;
		std::string	_field_name;


		ServerBlock 	_server;
		ServerLocation	_location;



	public:
		Request();
		Request(char *str);
		~Request();
		Request( Request const & src );
		Request & operator=( Request const & rhs );

		// Returns the index to which the parsing led
		size_t								parse_all(const char *str);
		const char							*parse(const char *str);
		std::string							extract_attribute(std::string req_copy, std::string terminating, const char **ptr, std::size_t residual_offset);
		void								manage_head(const char **ptr);
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

		void 								set_server(ServerBlock server);
		ServerBlock	const 					&get_server(void);

		void 								set_location(ServerLocation location);
		ServerLocation const 				&get_location(void);

};

std::ostream& operator<<(std::ostream&, const Request&);

#endif
