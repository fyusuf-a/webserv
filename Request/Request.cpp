#include "Request.hpp"

std::string	ft_strtrim(std::string str) {
	if (str == "")
		return "";
	return str.substr(str.find_first_not_of(" \n\r\v\t\f"), str.find_first_not_of(" \n\r\v\t\f") - str.find_last_not_of(" \n\r\v\t\f"));
}

std::string	extract_attribute(std::string req_copy, std::string terminating, char **ptr) {
	std::size_t	length;

	length = req_copy.find(terminating);
	if (length == std::string::npos) {
		(*ptr) += req_copy.length();
		return req_copy;
	}
	(*ptr) += length + terminating.length();
	return req_copy.substr(0, length);
}

char		*Request::parse(char *ptr) {
	std::string	req_copy = (std::string)ptr;
	std::size_t	idx;

	if ((std::string)ptr == "") {
		_over = false;
		return ptr;
	}
	switch(this->get_head()) {
		case 0:
			_method = extract_attribute(req_copy, " ", &ptr);
			++_head;
			while (*ptr == ' ')
				ptr++;
			break;
		case 1:
			_path = extract_attribute(req_copy, "\r\n", &ptr);
			idx = _path.find(' ');
			if (idx < _path.length()) {
				_protocol = ft_strtrim(_path.substr(_path.find(' '), _path.length()));
				_path = _path.substr(0, idx);
			}
			++_head;
			break;
		case 2:
			_header->insert(std::pair<std::string, std::string>
				(extract_attribute(req_copy, ":", &ptr), ft_strtrim(extract_attribute((std::string)ptr, "\r\n", &ptr))));
			break;
		case 3:
			++_head;
			if ((*_header)["Content-Length"] == "" && (*_header)["Transfer-Encoding"] == "")
				return ptr; 
			if (req_copy.find("\r\n\r\n") == std::string::npos)
				_over = false;
			_body = extract_attribute(req_copy, "\r\n\r\n", &ptr);
			break;
	}
	if (((std::string)ptr).find("\r\n") == 0 && _head == 2) {
		_head++;
		ptr += 2;
	}
	return ptr;
}

void								Request::set_code(int code) {
	this->_code = code;
}

int									Request::get_code(void) const {
	return this->_code;
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

Request::Request() : _head(0), _code(200), _over(true) {
	_header = new std::map<std::string, std::string>;
}

Request::Request(char *str) : _head(0), _code(200), _over(true) {
	_header = new std::map<std::string, std::string>;
	this->parse(str);
}

Request::~Request() {
	delete _header;
}
