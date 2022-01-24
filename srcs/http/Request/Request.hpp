#ifndef REQUEST_HPP
#define REQUEST_HPP
#include <cstddef>
#include <iostream>
#include <map>
#include <list>
#include "../../parsingConf/serverBlock.hpp"
#include "../../utils/Log.hpp"
#include "../../utils/HeaderMap.hpp"

class ServerBlock;

class Request
{
	public:
		typedef HeaderMap::header_map header_map;
		static Log& LOG;
	private:
		std::string	_method;
		std::string _path;
		std::string _original_request_path;
		std::string _protocol;
		header_map	_headers;
		std::string _body;
		int			_head;
		bool		_over;
		bool		_wrong;
		bool		_too_big_body;
		bool		_last_zero_read;
		std::string _residual;
		std::string	_field_name;
		size_t		_lctr;
		bool		_treated_by_middlewares;
		std::string _extra_path;
		std::string _query;
		bool		_is_script;
		unsigned long	_to_read;
		std::string	_file_extension;

		ServerBlock 	_server;
		ServerLocation	_location;



	public:
		Request();
		~Request();
		Request( Request const & src );
		Request & operator=( Request const & rhs );

		void								parse(std::string& buffer);
		std::string							extract_attribute(std::string& buffer, std::string terminating);
		void								manage_head(std::string &buffer);
		//void								checkIncompleteRequest(std::string& buffer) const;
		std::string const&					get_method(void) const;
		void								set_method(std::string method);
		std::string const&					get_path(void) const;
		std::string const&					get_protocol(void) const;
		header_map const&					get_headers(void) const;
		std::string const&					get_body(void) const;
		std::string const&					get_residual(void) const;
		int									get_head(void) const;
		bool								get_over(void) const;
		bool								get_wrong(void) const;
		bool								get_too_big_body(void) const;
		void								set_over(bool over);
		void								set_path(const std::string&);
		void								set_original_request_path(const std::string&);
		void								set_query(const std::string&);
		void								set_extra_path(const std::string&);
		std::string const&					get_query(void) const;
		std::string const&					get_extra_path(void) const;
		std::string const&					get_original_request_path(void) const;

		void 								set_server(ServerBlock server);
		ServerBlock	const 					&get_server(void) const;

		void 								set_location(ServerLocation location);
		ServerLocation 						&get_location(void);

		bool								get_treated_by_middlewares(void) const;
		void								set_treated_by_middlewares(bool);

		bool								get_is_script() const;
		void								set_is_script(bool);
};

std::ostream& operator<<(std::ostream&, const Request&);
std::ostream& operator<(std::ostream&, const Request&);

#endif
