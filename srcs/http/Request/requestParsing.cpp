#include "Request.hpp"

std::string	ft_strtrim(std::string str) {
	if (str == "" || str.find_first_not_of(" \n\r\v\t\f") == std::string::npos)
		return "";
	return str.substr(str.find_first_not_of(" \n\r\v\t\f"), str.find_first_not_of(" \n\r\v\t\f") - str.find_last_not_of(" \n\r\v\t\f"));
}

std::string	Request::extract_attribute(std::string req_copy, std::string terminating, std::string& str, std::size_t residual_offset) {
	std::size_t	length;

	length = req_copy.find(terminating);
	if (length == std::string::npos) {
		_over = false;
		str = str.substr(req_copy.length() - residual_offset);
		if (_residual == "")
			_residual = req_copy;
		return "";
	}
	str = str.substr(length + terminating.length() - residual_offset);
	return req_copy.substr(0, length);
}

void		Request::manage_head(std::string& str) {
	if (_head == 4) {
		//if (((std::string)*ptr).find("\r\n") == 0) {
		if (str.find("\r\n") == 0) {
			str = str.substr(2);
			//(*ptr) += 2;
			_head++;
		}
		else if (_over)
			_head--;
	}
	else if (_over)
		++_head;
}

std::string	&Request::parse(std::string& str) {

	while ((_head == 1 || _head == 2) && str[0] == ' ')
		str = str.substr(1);

	std::string	req_copy = _residual + str;
	std::size_t	residual_offset = _residual.length();
	std::string field_value;
	std::size_t i = 0;
	_over = true;
	_residual = "";

	if (str == "") {
		if (_head == 5)
			++_head;
		else
			_over = false;
		return str;
	}
	switch(this->get_head()) {
		case 0:
			_method = extract_attribute(req_copy, " ", str, residual_offset);
			break;
		case 1:
			_path = extract_attribute(req_copy, " ", str, residual_offset);
			break;
		case 2:
			_protocol = extract_attribute(req_copy, "\r\n", str, residual_offset);
			_protocol = ft_strtrim(_protocol);
			break;
		case 3:
			while (req_copy[i] == ' ')
				i++;
			if (req_copy.erase(0, i).find("\r\n") == 0 && i != 0)
			{
				str = str.substr(i);
				//ptr += i;
			}
			else
				_field_name = extract_attribute(req_copy, ":", str, residual_offset);
			break;
		case 4:
			field_value = ft_strtrim(extract_attribute(req_copy, "\r\n", str, residual_offset));
			if (_residual == "")
				_header->insert(std::pair<std::string, std::string>(_field_name, field_value));
			break;
		case 5:
			++_head;
			if ((*_header)["Content-Length"] == "" && (*_header)["Transfer-Encoding"] == "")
				return str;
			if (req_copy.find("\r\n\r\n") == std::string::npos){
				_over = false;
				--_head;
			}
			_body = extract_attribute(req_copy, "\r\n\r\n", str, residual_offset);
			return str;
	}
	manage_head(str);
	return str;
}

void	Request::parse_all(std::string &str) {
	bool keep_on_going = true;
	while (!str.empty()) {
		if (!keep_on_going)
			_over = true;
		while (_head < 6 && _over == true)
			str = parse(str);
		keep_on_going = _over;
	}
}
