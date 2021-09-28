#include "Request.hpp"

void			Request::check(void) {

}

int				Request::get_code(void) const {
	return this->_code;
}

ParsedRequest	Request::get_fields(void) const {
	return this->_fields;
}

Request & 		Request::operator=( Request const & rhs ){
	if (this != &rhs) {
		this->_fields = rhs.get_fields;
		this->_code = rhs.get_code;
	}
	return *this;
}
Request::Request( Request const & src ) {
	*this = src;
	return ;
}

Request::Request() _code(200) {
}

Request::Request( ParsedRequest req ) : _fields(req), _code(200) {
	this->check();
}

Request::~Request() {
}
