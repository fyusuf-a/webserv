#include "Request.hpp"

std::string	ft_strtrim(std::string str) {
	if (str == "" || str.find_first_not_of(" \n\r") == std::string::npos)
		return "";
	return str.substr(str.find_first_not_of(" \n\r"), str.find_last_not_of(" \n\r") - str.find_first_not_of(" \n\r") + 1);
}

std::string	Request::extract_attribute(std::string& buffer, std::string terminating) {
	std::size_t	length = 0;

	if (buffer.find("\r\n", _lctr) < buffer.find(terminating, _lctr))
		throw (400);
	length = buffer.find(terminating, _lctr) - _lctr;
	if (length == std::string::npos) {
		_over = false;
		return "";
	}
	_lctr += length + terminating.length();
	return buffer.substr(_lctr - length - terminating.length(), length);
}

void		Request::manage_head(std::string& buffer) {
	if (_head == 6)
		return ;
	if (_head == 4) {
		if (buffer.find("\r\n", _lctr) == _lctr) {
			_lctr += 2;
			_head++;
		}
		else if (_over)
			_head--;
	}
	else if (_over)
		++_head;
}

void		Request::parse(std::string& buffer) {
	_lctr = 0;
	while ((_head == 1 || _head == 2) && buffer[_lctr] == ' ')
		++_lctr;
	while (_head == 0 && (buffer[_lctr] == '\r' || buffer[_lctr] == '\n')) {
		++_lctr;
	}
	std::string field_value;
	_over = true;
	std::string tmp;

	if (buffer[_lctr] == '\0') {
		buffer = buffer.substr(_lctr);
		if (_head == 5)
			++_head;
		else
			_over = false;
		return;
	}
	switch(this->get_head()) {
		case 0:
			_method = extract_attribute(buffer, " ");
			break;
		case 1:
			_path = extract_attribute(buffer, " ");
			break;
		case 2:
			_protocol = extract_attribute(buffer, "\r\n");
			_protocol = ft_strtrim(_protocol);
			break;
		case 3:
			if (buffer.find("\r\n", _lctr) == 0) {
				_head = 6;
				_lctr += 2;
			}
			else
				_field_name = extract_attribute(buffer, ":");
			break;
		case 4:
			tmp = extract_attribute(buffer, "\r\n");
			field_value = ft_strtrim(tmp);
			if (_over)
				_headers.insert(std::pair<std::string, std::string>(_field_name, field_value));
			break;
		case 5:
			++_head;
			if (_headers.find("Content-Length") == _headers.end() && _headers.find("Transfer-Encoding") == _headers.end())
				break;
			if (buffer.find("\r\n\r\n") == std::string::npos && _method == "POST") {
				_over = false;
				--_head;
				break;
			}
			_body = extract_attribute(buffer, "\r\n\r\n");
	}
	manage_head(buffer);
	buffer = buffer.substr(_lctr);
	return ;
}
