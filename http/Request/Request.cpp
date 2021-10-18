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
		return "";
	}
	(*ptr) += length + terminating.length() - residual_offset;
	return req_copy.substr(0, length);
}

void		Request::manage_head(char **ptr) {
	while (_head < 2 && **ptr == ' ')
		(*ptr)++;
	if (_head == 4) {
		if (((std::string)*ptr).find("\r\n") == 0) {
			(*ptr) += 2;
			_head++;
		}
		else if (_over)
			_head--;
	}
	else if (_over)
		++_head;
}

char		*Request::parse(char *ptr) {
	std::string	req_copy = _residual + (std::string)ptr;
	std::size_t	residual_offset = _residual.length();
	std::string field_value;

	_over = true;
	_residual = "";
	if ((std::string)ptr == "") {
		if (_head == 5)
			++_head;
		else
			_over = false;
		return ptr;
	}
	switch(this->get_head()) {
		case 0:
			_method = extract_attribute(req_copy, " ", &ptr, residual_offset);
			break;
		case 1:
			_path = extract_attribute(req_copy, " ", &ptr, residual_offset);
			break;
		case 2:
			_protocol = extract_attribute(req_copy, "\r\n", &ptr, residual_offset);
			_protocol = ft_strtrim(_protocol);
			break;
		case 3:
//			if (ft_strtrim(req_copy).find("\r\n") == 0) {

//			}
//			else
			_field_name = extract_attribute(req_copy, ":", &ptr, residual_offset);
			break;
		case 4:
			field_value = ft_strtrim(extract_attribute(req_copy, "\r\n", &ptr, residual_offset));
			if (field_value != "") {
				_header->insert(std::pair<std::string, std::string>(_field_name, field_value));
			}
			break;
		case 5:
			++_head;
			if ((*_header)["Content-Length"] == "" && (*_header)["Transfer-Encoding"] == "")
				return ptr; 
			if (req_copy.find("\r\n\r\n") == std::string::npos){
				_over = false;
				--_head;
			}
			_body = extract_attribute(req_copy, "\r\n\r\n", &ptr, residual_offset);
			return ptr;
	}
	manage_head(&ptr);
	return ptr;
}

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
