#include "Request.hpp"

void								Request::set_over(bool over) {
	this->_over = over;
}

std::string							Request::get_method(void) const {
	return this->_method;
}

std::string							Request::get_path(void) const {
	return this->_path;
}

std::string							Request::get_protocol(void) const {
	return this->_protocol;
}

std::map<std::string, std::string>	*Request::get_header(void) const {
	return this->_header;
}

std::string							Request::get_body(void) const {
	return this->_body;
}

std::string							Request::get_residual(void) const {
	return this->_residual;
}

int									Request::get_head(void) const {
	return this->_head;
}

bool								Request::get_over(void) const {
	return this->_over;
}

Request & 		Request::operator=( Request const & rhs ){
	if (this != &rhs) {
		this->_method = rhs.get_method();
		this->_path = rhs.get_path();
		this->_protocol = rhs.get_protocol();
		this->_header = rhs.get_header();
		this->_body = rhs.get_body();
		this->_head = rhs.get_head();
		this->_over = rhs.get_over();
	}
	return *this;
}
Request::Request( Request const & src ) {
	*this = src;
	return ;
}

Request::Request() : _head(0), _over(true) {
	_header = new std::map<std::string, std::string>;
}

Request::Request(char *str) : _head(0), _over(true) {
	_header = new std::map<std::string, std::string>;
	this->parse(str);
}

Request::~Request() {
	delete _header;
}
