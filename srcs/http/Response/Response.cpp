#include "Response.hpp"

void				Response::set_code(Response::http_code code) {
	this->_code = code;
}

Response::http_code					Response::get_code(void) const {
	return this->_code;
}

Response & 		Response::operator=( Response const & rhs ){
	if (this != &rhs)
		this->_code = rhs._code;
	return *this;
}
Response::Response( Response const & src ) {
	*this = src;
	return ;
}

Response::Response() : _code(OK) {
}

Response::~Response() {
}
