#include "Request.hpp"

std::string	ft_strtrim(std::string str) {
	if (str == "" || str.find_first_not_of(" \n\r\v\t\f") == std::string::npos)
		return "";
	return str.substr(str.find_first_not_of(" \n\r\v\t\f"), str.find_first_not_of(" \n\r\v\t\f") - str.find_last_not_of(" \n\r\v\t\f"));
}

std::string	Request::extract_attribute(std::string req_copy, std::string terminating, const char **ptr, std::size_t residual_offset) {
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

void		Request::manage_head(const char **ptr) {
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

size_t		Request::parse_all(const char *ptr) {
	bool		nouveau = true;
	const char *new_ptr = ptr;
	size_t		char_count = 0;

	while (*ptr) {
		/*if (nouveau)
			return ;
		else*/
		if (!nouveau)
			set_over(true);
		set_over(true);
		while (get_head() < 6 && get_over() == true)
		{
			new_ptr = parse(ptr);
			char_count += new_ptr - ptr;
			ptr = new_ptr;
		}
		nouveau = get_over();
	}
	return char_count;
}

const char		*Request::parse(const char *ptr) {

	while ((_head == 1 || _head == 2) && *ptr == ' ')
		ptr++;

	std::string	req_copy = _residual + (std::string)ptr;
	std::size_t	residual_offset = _residual.length();
	std::string field_value;
	std::size_t i = 0;
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
			while (req_copy[i] == ' ')
				i++;
			if (req_copy.erase(0, i).find("\r\n") == 0 && i != 0)
				ptr += i;
			else
				_field_name = extract_attribute(req_copy, ":", &ptr, residual_offset);
			break;
		case 4:
			field_value = ft_strtrim(extract_attribute(req_copy, "\r\n", &ptr, residual_offset));
			if (_residual == "")
			{
				//std::cerr << "_header " << &_header << " of size " << _header.size() << std::endl;
				//std::cerr << "_field_name " << _field_name << std::endl;
				//std::cerr << "field_value " << field_value << std::endl;
				_header.insert(std::pair<std::string, std::string>(_field_name, field_value));
				//std::cerr << "lol" << std::endl;
			}
			break;
		case 5:
			++_head;
			if (_header["Content-Length"] == "" && _header["Transfer-Encoding"] == "")
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
