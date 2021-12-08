#include "Request.hpp"
#include <stdlib.h>

std::string	ft_strtrim(std::string str) {
	if (str == "" || str.find_first_not_of(" \n\r") == std::string::npos)
		return "";
	return str.substr(str.find_first_not_of(" \n\r"), str.find_last_not_of(" \n\r") - str.find_first_not_of(" \n\r") + 1);
}

std::string	Request::extract_attribute(std::string& buffer, std::string terminating) {
	std::size_t	length = 0;

	if (buffer.find("\r\n\r\n", _lctr) < buffer.find(terminating, _lctr)) {
		_head = 6;
		terminating = "\r\n\r\n";
		_wrong = true;
	}
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
	if (_head == 5)
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
	std::string body_chunk;
	_over = true;
	std::string tmp;

	if (buffer[_lctr] == '\0') {
		buffer = buffer.substr(_lctr);
		if (_head == 5 && _headers.find("Content-Length") == _headers.end() && _headers.find("Transfer-Encoding") == _headers.end())
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
			if (buffer.find("\r\n", _lctr) == 0)
				_head = 4;
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
			if (_method == "POST" && _headers.find("Content-Length") != _headers.end()) {
				if (_to_read == 0)
					_to_read = ::atoi(_headers["Content-Length"].c_str());
				if (buffer.length() >= _to_read) {
					_body += buffer.substr(_lctr, _to_read);
					_lctr += _to_read;
					_to_read = 0;
					++_head;
				}
				else {
					_body += buffer.substr(_lctr, buffer.length());
					_to_read -= buffer.length();
					_lctr += buffer.length();
					_over = false;
				}
			}
			else if (_method == "POST" && _headers.find("Transfer-Encoding") != _headers.end()) {
				if (_to_read == 0) {
					_to_read = std::strtoul(extract_attribute(buffer, "\r\n").c_str(), NULL, 16);
				}
				if (buffer.find("\r\n", _lctr) - _lctr == 0) {
					_lctr += 2;
					++_head;
					break ;
				}
				body_chunk = extract_attribute(buffer, "\r\n");
				_body += body_chunk;
				if (body_chunk != "")
					_to_read = 0;
			}
	}
	manage_head(buffer);
	buffer = buffer.substr(_lctr);
	return ;
}
