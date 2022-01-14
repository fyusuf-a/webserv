#include "HeaderMap.hpp"

std::string	HeaderMap::get_header_first_value(header_map const& headers, std::string const& name) {
	header_map::const_iterator it = headers.find(name);
	if (it == headers.end())
		throw std::out_of_range("no such header");
	if (it->second.empty())
		throw std::out_of_range("no header-value");
	return (list_front(it->second));
}

void	HeaderMap::set_header(header_map& headers, std::string const& header_name, std::string const& header_value, bool replace) {
	header_map::iterator it = headers.find(header_name);
	if (it == headers.end())
		headers.insert(std::pair<std::string, std::list<std::string> >(header_name, std::list<std::string>(1, header_value)));
	else {
		if (replace)
			it->second.clear();
		it->second.push_front(header_value);
	}
}

std::ostream& operator<<(std::ostream& os, const HeaderMap::header_map& headers) {
	for (HeaderMap::header_map::const_iterator it = headers.begin(); it != headers.end() ; it++) {
		for (std::list<std::string>::const_iterator jt = it->second.begin(); jt != it->second.end(); jt++) {
			os << it->first << ": " << *jt << "\r\n";
		}
	}
	return os;
}
