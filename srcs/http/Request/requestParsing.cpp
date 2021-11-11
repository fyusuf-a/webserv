#include "Request.hpp"

std::string	ft_strtrim(std::string str) {
	if (str == "" || str.find_first_not_of(" \n\r\v\t\f") == std::string::npos)
		return "";
	return str.substr(str.find_first_not_of(" \n\r\v\t\f"), str.find_first_not_of(" \n\r\v\t\f") - str.find_last_not_of(" \n\r\v\t\f"));
}

std::string	Request::extract_attribute(std::string& buffer, std::string terminating) {
	std::size_t	length = 0;

	length = buffer.find(terminating, _lctr);
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

void		Request::deal_header_empty_line(std::string& buffer) {
	std::size_t end = buffer.find("\r\n", _lctr);

	if (end == 0)
		_head = 4;
	else {
		_shadow_header.push_back(extract_attribute(buffer, "\r\n"));
		_head = 2;	
	}
}

void		Request::parse(std::string& buffer) {
	_lctr = 0;
	while ((_head == 1 || _head == 2) && buffer[0] == ' ')
		++_lctr;

	std::string field_value;
	_over = true;

	if (buffer[0] == '\0') {
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
			if (buffer.find("\r\n", _lctr) < buffer.find(":", _lctr))
				deal_header_empty_line(buffer);
			else
				_field_name = extract_attribute(buffer, ":");
			break;
		case 4:
			field_value = ft_strtrim(extract_attribute(buffer, "\r\n"));
			if (_over)
				_header.insert(std::pair<std::string, std::string>(_field_name, field_value));
			break;
		case 5:
			++_head;
			if (_header.find("Content-Length") == _header.end() && _header.find("Transfer-Encoding") == _header.end())
				break;
			if (buffer.find("\r\n\r\n") == std::string::npos) {
				_over = false;
				--_head;
				break;
			}
			_body = extract_attribute(buffer, "\r\n\r\n");
	}
	std::cout << "head & over " << _head << _over << std::endl;
	manage_head(buffer);
	buffer = buffer.substr(_lctr);
	std::cout << "head & over " << _head << _over << std::endl;
	return ;
}
