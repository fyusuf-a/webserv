#ifndef REQUEST_HPP
# define REQUEST_HPP
#include <cstddef>
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
		std::map<std::string, std::string>	_headers;
		std::string _body;
		int			_head;
		bool		_over;
		std::string _residual;
		std::string	_field_name;
		size_t		_lctr;
		bool		_treated_by_middlewares;
		std::string _extra_path;
		std::string _query;

		ServerBlock 	_server;
		ServerLocation	_location;



	public:
		Request();
		Request(std::string& buffer);
		~Request();
		Request( Request const & src );
		Request & operator=( Request const & rhs );

		void								reinitialize();
		void								parse(std::string& buffer);
		std::string							extract_attribute(std::string& buffer, std::string terminating);
		void								manage_head(std::string &buffer);
		//void								checkIncompleteRequest(std::string& buffer) const;
		std::string							get_method(void) const;
		std::string							get_path(void) const;
		std::string							get_protocol(void) const;
		std::map<std::string, std::string>	const& get_headers(void) const;
		std::string							get_body(void) const;
		std::string							get_residual(void) const;
		int									get_head(void) const;
		bool								get_over(void) const;
		void								set_over(bool over);
		void								set_path(std::string path);
		void								set_query(std::string path);
		void								set_extra_path(std::string path);
		std::string							get_query(void) const;
		std::string							get_extra_path(void) const;

		void 								set_server(ServerBlock server);
		ServerBlock	const 					&get_server(void) const;

		void 								set_location(ServerLocation location);
		ServerLocation const 				&get_location(void) const;

		bool								get_treated_by_middlewares(void) const;
		void								set_treated_by_middlewares(bool);
};

std::ostream& operator<<(std::ostream&, const Request&);

#endif
