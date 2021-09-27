#include "ParsedRequest.hpp"

std::string	extract_attribute(std::string req_copy, std::string terminating, char **ptr) {
	std::size_t	length;
	std::string	attribute;

	length = req_copy.find(terminating);
	attribute = req_copy.substr(0, length);
	(*ptr) += length + terminating.length();
	return attribute;
}

char		*ParsedRequest::parse(char *ptr) {
	std::string	req_copy = (std::string)ptr;
	std::size_t	length;

	switch(this->get_head()) {
		case 0:
			_method = extract_attribute(req_copy, " ", &ptr);
			++_head;
			break;
		case 1:
			_path = extract_attribute(req_copy, " ", &ptr);
			++_head;
			break;
		case 2:
			_protocol = extract_attribute(req_copy, "\r\n", &ptr);
			++_head;
			break;
		case 3:
			_header.insert(std::pair<std::string, std::string>(extract_attribute(req_copy, " ", &ptr), extract_attribute((std::string)ptr, "\r\n", &ptr)));
			break;
		case 4:
			_body.insert(std::pair<std::string, std::string>(extract_attribute(req_copy, " ", &ptr), extract_attribute((std::string)ptr, "\r\n", &ptr)));
			break;
	}
	if (((std::string)ptr).find("\r\n") == 0) {
		_head++;
		ptr += 2;
	}
	return (ptr);
}

std::string							ParsedRequest::get_method(void) const {
	return this->_method;
}

std::string							ParsedRequest::get_path(void) const {
	return this->_path;
}

std::string							ParsedRequest::get_protocol(void) const {
	return this->_protocol;
}

std::map<std::string, std::string>	ParsedRequest::get_header(void) const {
	return this->_header;
}

std::map<std::string, std::string>	ParsedRequest::get_body(void) const {
	return this->_body;
}

int									ParsedRequest::get_head(void) const {
	return this->_head;
}

ParsedRequest & 		ParsedRequest::operator=( ParsedRequest const & rhs ){
	if (this != &rhs) {
		this->_method = rhs.get_method();
		this->_path = rhs.get_path();
		this->_protocol = rhs.get_protocol();
		this->_header = rhs.get_header();
		this->_body = rhs.get_body();
		this->_head = rhs.get_head();
	}
	return *this;
}
ParsedRequest::ParsedRequest( ParsedRequest const & src ) {
	*this = src;
	return ;
}

ParsedRequest::ParsedRequest() : _head(0) {
}

ParsedRequest::~ParsedRequest() {
}
