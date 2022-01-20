#include "Response.hpp"
#include "../../server/ActiveHTTP.hpp"
#include <string>

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
		case 204:
			return "No Content";
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
		case 413:
			return "Payload Too Large";
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
			return "I'm a teapot";
	}
}

void					Response::set_code(unsigned int code) {
	this->_code = code;
}

void					Response::set_index_display(bool status) {
	this->_index_display = status;
}

unsigned int 			Response::get_code(void) const {
	return (http_code)this->_code;
}

std::string		Response::get_body(void) const {
	return this->_body;
}

bool			Response::get_index_display(void) const {
	return this->_index_display;
}

const Response::header_map& Response::get_headers() const {
	return _headers;
}

void	Response::set_header(const std::string& key, const std::string& value,
		bool replace) {
	HeaderMap::set_header(_headers, key, value, replace);
}

void	Response::delete_header(const std::string& key) {
	_headers.erase(key);
}

void			Response::set_body(std::string body)
{
	this->_body += body;
}

Response & 		Response::operator=( Response const & rhs ){
	if (this != &rhs)
	{
		_custom_reason_phrase = rhs._custom_reason_phrase;
		_code = rhs._code;
		_index_display = rhs._index_display;
		_body = rhs._body;
		_headers = rhs._headers;
		_ready = rhs._ready;
		_beginning_written_on_write_buffer = rhs._beginning_written_on_write_buffer;
		_written_on_write_buffer = rhs._beginning_written_on_write_buffer;
	}
	return *this;
}
Response::Response( Response const & src ) {
	*this = src;
}

Response::Response() : _code(OK), _ready(false), _beginning_written_on_write_buffer(false), _index_display(false) {
					   //, _written_on_write_buffer(false) {
}

Response::~Response() {
}

void Response::ready() {
	LOG.debug() << "Response is ready" << std::endl;
	_ready = true;
}

bool Response::get_ready() {
	return _ready;
}

bool Response::get_beginning_written_on_write_buffer() const {
	return _beginning_written_on_write_buffer;
}

std::string const& Response::get_custom_reason_phrase() const {
	return _custom_reason_phrase;
}

/*bool Response::get_written_on_write_buffer() const {
	return _written_on_write_buffer;
}*/

void Response::set_beginning_written_on_write_buffer(bool set) {
	_beginning_written_on_write_buffer = set;
}

//void Response::set_written_on_write_buffer(bool set) {
	//_written_on_write_buffer = set;
//}

void 		Response::set_custom_reason_phrase(const std::string& reason_phrase) {
	_custom_reason_phrase = reason_phrase;
}

std::ostream& operator<<(std::ostream& os, const Response& resp) {
	os < resp;
	os << resp.get_body(); 
	return os;
}

std::ostream& operator<(std::ostream& os, const Response& resp) {
	std::string const& custom_reason_phrase = resp.get_custom_reason_phrase();
	os << SERVER_PROTOCOL << " " << resp.get_code() << " ";
	if (custom_reason_phrase.empty())
		os << Response::http_code_to_str(static_cast<Response::http_code>(resp.get_code()));
	else
		os << resp.get_custom_reason_phrase();
	os << "\r\n";
	os << resp.get_headers();
	os << "\r\n";
	return os;
}
