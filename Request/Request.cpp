#include "Request.hpp"
#include <list>

int				Request::check_header(void) {
	std::list<std::string>				headers;
	size_t								count = 0;
	std::list<std::string>::iterator	iter = headers.begin();

	headers.push_back("Accept");
	headers.push_back("Accept-Charset");
	headers.push_back("Accept-Encoding");
	headers.push_back("Accept-Language");
	headers.push_back("Accept-Ranges");
	headers.push_back("Age");
	headers.push_back("Allow");
	headers.push_back("Authorization");
	headers.push_back("Cache-Control");
	headers.push_back("Connection");
	headers.push_back("Content_Encoding");
	headers.push_back("Content_Language");
	headers.push_back("Content_Length");
	headers.push_back("Content_Location");
	headers.push_back("Content_MD5");
	headers.push_back("Content_Range");
	headers.push_back("Content_Type");
	headers.push_back("Date");
	headers.push_back("Etag");
	headers.push_back("Expect");
	headers.push_back("Expires");
	headers.push_back("From");

	while (iter != headers.end()) {
		if (this->_fields.get_header()[*iter] != "")
			++count;
		iter++;
	}
	if (count != this->_fields.get_header().size())
		return (1);
	return (0);
}

void			Request::check(void) {
	std::string met = _fields.get_method();
	if (met != "GET" && met != "POST" && met != "DELETE")
		throw(501);

	if (_fields.get_path()[0] != '/')
		throw(400);

	if (_fields.get_protocol() != "HTTP/1.1")
		throw(505);

	if (check_header())
		throw(400);

}

int				Request::get_code(void) const {
	return this->_code;
}

ParsedRequest	Request::get_fields(void) const {
	return this->_fields;
}

Request & 		Request::operator=( Request const & rhs ){
	if (this != &rhs) {
		this->_fields = rhs.get_fields();
		this->_code = rhs.get_code();
	}
	return *this;
}
Request::Request( Request const & src ) {
	*this = src;
	return ;
}

Request::Request() : _code(200) {
}

Request::Request( ParsedRequest req ) : _fields(req), _code(200) {
	try { this->check(); }
	catch (int code) { _code = code; std::cout << code << std::endl;};
}

Request::~Request() {
}
