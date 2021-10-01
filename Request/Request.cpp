#include "Request.hpp"
#include <list>

void			Request::check(void) {
	std::string met = _fields.get_method();
	if (met != "GET" && met != "POST" && met != "DELETE")
		throw(501);

	if (_fields.get_path()[0] != '/')
		throw(400);

	if (_fields.get_protocol() != "HTTP/1.1")
		throw(505);

	std::list<std::string> headers;
	headers.push_back("Date");
	headers.push_back("Content_Type");
	headers.push_back("Content_Base");
	std::list<std::string>::iterator iter = headers.begin();
	std::cout << _fields.get_header().size() << std::endl;
	while (iter != headers.end()) {

		if (_fields.get_header()[*iter] != "")
			std::cout << *iter << std::endl;
		else
			std::cout << "no" << std::endl;
		iter++;
	}
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
