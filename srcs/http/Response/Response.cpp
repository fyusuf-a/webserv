#include "Response.hpp"
#include "../../server/ActiveHTTP.hpp"

Log &Response::LOG = Log::getInstance();

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

const std::map<std::string, std::string>& Response::get_headers() const {
	return _header;
}

void	Response::set_header(const std::string& key, const std::string& value) {
	_header[key] = value;
}

void	Response::delete_header(const std::string& key) {
	_header.erase(key);
}

void			Response::set_body(std::string body)
{
	this->_body += body;
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

Response::Response() : _code(OK), _ready(false), _beginning_sent(false)
					   , _sent(false)
					   , _delegated_to_task(false) {
}

Response::~Response() {
}

void Response::ready() {
	LOG.debug() << "Response is ready" << std::endl;
	_ready = true;
}

void Response::reinitialize() {
	_code = OK;
	_ready = false;
	_body = "";
	_beginning_sent = false;
	_sent = false;
	_delegated_to_task = false;
}

bool Response::get_ready() {
	return _ready;
}

bool Response::get_beginning_sent() const {
	return _beginning_sent;
}

bool Response::get_sent() const {
	return _sent;
}

bool Response::get_delegated_to_task() const {
	return _delegated_to_task;
}

void Response::set_beginning_sent(bool set) {
	_beginning_sent = set;
}

void Response::set_sent(bool set) {
	_sent = set;
}

void Response::set_delegated_to_task(bool set) {
	_delegated_to_task = set;
}

/*static std::ostream& put_headers(std::ostream& os, const Response& resp) {
	for (std::map<std::string, std::string>::const_iterator it =
			resp.get_headers().begin(); it != resp.get_headers().end(); ++it)
		os << it->first << ":" << it->second << "\r\n";
	return os;
}*/

std::ostream& operator<<(std::ostream& os, const Response& resp) {
	os < resp;
	os << resp.get_body(); 
	return os;
}

std::ostream& operator<(std::ostream& os, const Response& resp) {
	os << "HTTP/1.1 " << resp.get_code() << " "
		<< Response::http_code_to_str(resp.get_code()) << "\r\n";
	for (std::map<std::string, std::string>::const_iterator it =
			resp.get_headers().begin(); it != resp.get_headers().end(); ++it)
		os << it->first << ":" << it->second << "\r\n";
	os << "\r\n";
	return os;
}
