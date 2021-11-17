#ifndef RESPONSE_HPP
# define RESPONSE_HPP
# include <iostream>
# include "../Request/Request.hpp"



class ActiveHTTP;

class Response
{
	public:
		enum http_code {

			// Succes
			OK = 200,
			Created = 201,
			Accepted = 202,

			// Redirection
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

			// Erreur Server
			NotImplemented = 501,
			HTTPNotSupported = 505,
			UnknownError = 520,
			WebServerIsDown = 521,
			ConnectionTimedOut = 522,
			OriginIsUnreachable = 523,
			ATimeoutOccurred = 524
		};
	
	private:
		http_code	_code;
		std::string _body;

		bool		_ready;

	public:
		static std::string http_code_to_str(http_code);
	
		Response();
		~Response();
		Response( Response const & src );
		Response & operator=( Response const & rhs );

		http_code		get_code(void) const;
		void			set_code(http_code code);

		std::string	get_body(void) const;
		void			set_body(std::string body);



		void		send();
		void		reinitialize();
		bool		get_ready();
};

std::ostream& operator<<(std::ostream&, const Response&);

#endif
