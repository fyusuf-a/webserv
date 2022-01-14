#ifndef HEADERNAME_HPP
#define HEADERNAME_HPP

#include <iostream>
#include <list>
#include <map>
#include "utils.hpp"

namespace HeaderMap {
	typedef std::map<std::string, std::list<std::string>, Utils::cmpStringInsensitive> header_map;
	std::string	get_header_first_value(header_map const&, std::string const& name);
	void set_header(header_map&, std::string const& header_name, std::string const& header_value, bool replace = false);
};

std::ostream& operator<<(std::ostream&, const HeaderMap::header_map&);

#endif
