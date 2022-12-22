#ifndef RESPONSE_HPP
# define RESPONSE_HPP
# include <iostream>
# include "../Request/Request.hpp"
# include "../../utils/Log.hpp"
# include "../../utils/utils.hpp"
# include "../../utils/HeaderMap.hpp"

class ActiveHTTP;

class Response
{
	public:
		typedef HeaderMap::header_map header_map;
		enum http_code {
			// Success
			OK = 200,
			Created = 201,
			Accepted = 202,
			NoContent = 204,
			// Redirection1
			MultipleChoices = 300,
			MovedPermanently = 301,
			Found = 302,
			SeeOther = 303,
			NotModified = 304,
			// Erreur
			BadRequest = 400,
			Unauthorized = 401,
			Forbidden = 403,
			NotFound = 404,
			MethodNotAllowed = 405,
			NotAcceptable = 406,
			RequestTime_out = 408,
			PayloadTooLarge = 413,
			// Server Error
			InternalServerError = 500,
			NotImplemented = 501,
			HTTPNotSupported = 505,
			UnknownError = 520,
			WebServerIsDown = 521,
			ConnectionTimedOut = 522,
			OriginIsUnreachable = 523,
			ATimeoutOccurred = 524
		};
	
	protected:
		// The CGI might change the status code and the reason phrase, hence,
		// the following string, set to "" initially, tracks this
		std::string _custom_reason_phrase;
		unsigned int _code;
		std::string _body;
		header_map	_headers;

		/*
		 * The lifetime of a response is :
		 * request._treated_by_middlewares
		 * (-> _beginning_written_on_write_buffer)
		 * -> _written_on_write_buffer
		 */

		// If a task is running, enables it only if the first part of the
		// request is sent
		bool		_beginning_written_on_write_buffer;
		bool		_written_on_write_buffer;

		bool		_index_display;

	public:
		static std::string http_code_to_str(http_code);
	
		Response();
		~Response();
		Response( Response const & src );
		Response & operator=( Response const & rhs );

		std::string	get_body(void) const;
		const header_map&	get_headers() const;
		void				delete_header(const std::string& key);
		unsigned int		get_code(void) const;
		bool				get_index_display() const;
		bool 				get_beginning_written_on_write_buffer() const;
		bool 				get_written_on_write_buffer() const;
		std::string const&	get_custom_reason_phrase() const;

		void		set_code(unsigned int code);
		void		set_header(const std::string& key, const std::string& value,
											bool replace);
		void		set_index_display(bool status);
		void		set_body(std::string body);
		void		set_beginning_written_on_write_buffer(bool);
		void 		set_written_on_write_buffer(bool);
		void 		set_custom_reason_phrase(const std::string&);

		static Log& LOG;
};

std::ostream& operator<<(std::ostream&, const Response&);
// Attention, the following method is to print only the status line and the
// headers
std::ostream& operator<(std::ostream&, const Response&);

#endif
