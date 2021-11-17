#include "Response.hpp"
#include "../../server/ActiveHTTP.hpp"

std::string Response::http_code_to_str(http_code code) {
	switch (code) {
		case 200:
			return "OK";
		break;
		case 201:
			return "Created";
		break;
		case 202:
			return "Accepted";
		break;
		case 300:
			return "Multiple Choices";
		break;
		case 301:
			return "Moved Permanently";
		break;
		case 302:
			return "Found";
		break;
		case 303:
			return "See Other";
		break;
		case 304:
			return "Not Modified";
		break;
		case 400:
			return "Bad Request";
		break;
		case 401:
			return "Unauthorized";
		break;
		case 403:
			return "Forbidden";
		break;
		case 404:
			return "Not Found";
		break;
		case 405:
			return "Method Not Allowed";
		break;
		case 406:
			return "Not Acceptable";
		break;
		case 408:
			return "Request Timeout";
		break;
		case 501:
			return "Not Implemented";
		break;
		case 505:
			return "HTTP Not Supported";
		break;
		case 520:
			return "Unknown Error";
		break;
		case 521:
			return "Web Server Is Down";
		break;
		case 522:
			return "Connection Timed Out";
		break;
		case 523:
			return "Origin Is Unreachable";
		break;
		case 524:
			return "A Timeout Occurred";
		break;
		default:
			return "Unknown Error";
	}
}

void					Response::set_code(Response::http_code code) {
	this->_code = code;
}
Response::http_code		Response::get_code(void) const {
	return this->_code;
}

std::string		Response::get_body(void) const {
	return this->_body;
}
void			Response::set_body(std::string body)
{
	this->_body = body;
}




Response & 		Response::operator=( Response const & rhs ){
	if (this != &rhs)
	{
		this->_code = rhs._code;
		_ready = rhs._ready;
	}
	return *this;
}
Response::Response( Response const & src ) {
	*this = src;
}

Response::Response() : _code(OK), _ready(false) {
}

Response::~Response() {
}

void Response::send() {
	_ready = true;
}

void Response::reinitialize() {
	_code = OK;
	_ready = false;
}

bool Response::get_ready() {
	return _ready;
}

std::ostream& operator<<(std::ostream& os, const Response& resp) {
	os << "HTTP/1.1 " << resp.get_code() << " "
		<< Response::http_code_to_str(resp.get_code())
		<< "\r\nContent-Length: " << resp.get_body().length()
		<< "\r\n\r\n" << resp.get_body();
	return os;
}
