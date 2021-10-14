#include "Request.hpp"

std::string	ft_strtrim(std::string str) {
	if (str == "")
		return "";
	return str.substr(str.find_first_not_of(" \n\r\v\t\f"), str.find_first_not_of(" \n\r\v\t\f") - str.find_last_not_of(" \n\r\v\t\f"));
}

std::string	Request::extract_attribute(std::string req_copy, std::string terminating, char **ptr, std::size_t residual_offset) {
	std::size_t	length;

	length = req_copy.find(terminating);
	if (length == std::string::npos) {
		_over = false;
		(*ptr) += req_copy.length() - residual_offset;
		if (_residual == "")
			_residual = req_copy;
		if (_head != 2)
			_head--;
		return "";
	}
	(*ptr) += length + terminating.length() - residual_offset;
	return req_copy.substr(0, length);
}

char		*Request::parse(char *ptr) {
	std::string	req_copy = _residual + (std::string)ptr;
	std::size_t	residual_offset = _residual.length();
	std::size_t	idx;
	std::string field_name;
	std::string field_value;

	_over = true;
	_residual = "";
	if ((std::string)ptr == "") {
		if (_head == 3)
			++_head;
		else
			_over = false;
		return ptr;
	}
	switch(this->get_head()) {
		case 0:
			_method = extract_attribute(req_copy, " ", &ptr, residual_offset);
			++_head;
			while (*ptr == ' ')
				ptr++;
			break;
		case 1:
			_path = extract_attribute(req_copy, "\r\n", &ptr, residual_offset);
			idx = _path.find(' ');
			if (idx < _path.length()) {
				_protocol = ft_strtrim(_path.substr(_path.find(' '), _path.length()));
				_path = _path.substr(0, idx);
			}
			++_head;
			break;
		case 2:
			field_name = extract_attribute(req_copy, ":", &ptr, residual_offset / 2);
			field_value = ft_strtrim(extract_attribute(req_copy.substr(field_name.length() + 1, req_copy.length()), "\r\n", &ptr, (residual_offset + 1) / 2));
			if (_residual != "")
				_residual = field_name + ":" + _residual;
			else
				_header->insert(std::pair<std::string, std::string>(field_name, field_value));
			break;
		case 3:
			++_head;
			if ((*_header)["Content-Length"] == "" && (*_header)["Transfer-Encoding"] == "")
				return ptr; 
			if (req_copy.find("\r\n\r\n") == std::string::npos){
				_over = false;
			}
			_body = extract_attribute(req_copy, "\r\n\r\n", &ptr, residual_offset);
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

void								Request::set_over(bool over) {
	this->_over = over;
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
