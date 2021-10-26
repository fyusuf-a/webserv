#include "Response.hpp"


void				Response::set_code(int code) {
	this->_code = code;
}

int					Response::get_code(void) const {
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

Response::Response() : _code(200) {
}

Response::~Response() {
}
