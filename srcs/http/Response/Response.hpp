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
			Unauthoried = 401,
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
		ActiveHTTP* _server;
		http_code	_code;

	public:
		Response();
		Response(ActiveHTTP* callback);
		~Response();
		Response( Response const & src );
		Response & operator=( Response const & rhs );

		void		set_code(http_code code);
		void		send();
		http_code	get_code(void) const;
};

std::ostream& operator<<(std::ostream&, const Response&);

#endif
