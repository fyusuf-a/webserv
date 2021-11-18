#include "serverLocation.hpp"


ServerLocation::ServerLocation() :
_root(""), _cgi_ext(""), _cgi_bin(""), _language(""), _auth_basic_file(""), _location_path(""), _auto_index(0), _auth_basic(0), _body_size(-1){}

ServerLocation::ServerLocation(const ServerLocation &other) :
_index(other._index), _methods(other._methods), _root(other._root), _cgi_ext(other._cgi_ext),
_cgi_bin(other._cgi_bin), _language(other._language), _auth_basic_file(other._auth_basic_file),
_location_path(other._location_path), _auto_index(other._auto_index), _auth_basic(other._auth_basic), _body_size(other._body_size){}

ServerLocation::~ServerLocation(){}
    
ServerLocation &ServerLocation::operator=(const ServerLocation &other)
{
    if (this != &other)
	{
		_index = other._index;
		_methods = other._methods;
		_cgi_ext = other._cgi_ext;
		_cgi_bin = other._cgi_bin;
		_language = other._language;
		_auto_index = other._auto_index;
		_auth_basic = other._auth_basic;
		_auth_basic_file = other._auth_basic_file;
		_body_size = other._body_size;
		_location_path = other._location_path;
		_root = other._root;
	}
    return (*this);
}

void                             ServerLocation::set_index(std::vector<std::string> const &index){ this->_index = index; }
void                             ServerLocation::set_methods(std::vector<std::string> const &methods){ this->_methods = methods; }
void                             ServerLocation::set_root(std::string const &root){ this->_root = root; }
void                             ServerLocation::set_cgi_ext(std::string const &cgi_ext){ this->_cgi_ext = cgi_ext; }
void                             ServerLocation::set_cgi_bin(std::string const &cgi_bin){ this->_cgi_bin = cgi_bin; }
void                             ServerLocation::set_language(std::string const &language){ this->_language = language; }
void                             ServerLocation::set_auth_basic_file(std::string const &path){ this->_auth_basic_file = path; }
void                             ServerLocation::set_location_path(std::string const &path){ this->_location_path = path; }
void                             ServerLocation::set_auth_basic(bool n){this->_auth_basic = n; }
void                             ServerLocation::set_auto_index(bool n){ this->_auto_index = n; }
void                             ServerLocation::set_body_size(size_t val){ this->_body_size = val; }

std::vector<std::string> const   &ServerLocation::get_index(void) const{ return (this->_index); }
std::vector<std::string> const   &ServerLocation::get_methods(void) const{ return (this->_methods); }
std::string const                &ServerLocation::get_root(void) const{ return (this->_root); }
std::string const                &ServerLocation::get_cgi_ext(void) const{ return (this->_cgi_ext); }
std::string const                &ServerLocation::get_cgi_bin(void) const{ return (this->_cgi_bin); }
std::string const                &ServerLocation::get_language(void) const{ return (this->_language); }
std::string const                &ServerLocation::get_auth_basic_file(void) const{ return (this->_auth_basic_file); }
std::string const                &ServerLocation::get_location_path(void) const{ return (this->_location_path); }
bool                              ServerLocation::get_auto_index(void) const{ return (this->_auto_index); }
bool                              ServerLocation::get_auth_basic(void) const{ return (this->_auth_basic); }
size_t                            ServerLocation::get_body_size(void) const{ return (this->_body_size); }




std::ostream& operator<<(std::ostream& os, const ServerLocation& location) {
	os << "location " + location.get_location_path() << std::endl << "{" << std::endl;
	if (!location.get_index().empty())
		os << "index\t" <<  location.get_index() << ";" << std::endl;
	
	std::string val = "off";
	if (location.get_auto_index())
		val = "on";
	os << "autoindex\t" << val << ";" << std::endl;
	
	if (!location.get_methods().empty())
		os << "methods\t" << location.get_methods() << ";" << std::endl;
	if (!location.get_root().empty())
		os << "root\t" << location.get_root() << ";" << std::endl;
	if (!location.get_cgi_ext().empty())
		os << "cgi_extension\t" << location.get_cgi_ext() << ";" << std::endl;
	if (!location.get_cgi_bin().empty())
		os << "cgi_bin\t" << location.get_cgi_bin() << ";" << std::endl;
	os << "client_max_body_size\t" << location.get_body_size() << ";" << std::endl;
		
	val = "off";
	if (location.get_auto_index())
		val = "on";
	os << "auth_basic\t" << val << ";" << std::endl;

	if (!location.get_auth_basic_file().empty())
		os << "auth_basic_user_file\t" << location.get_auth_basic_file() << ";" << std::endl;
	if (!location.get_language().empty())
		os << "language\t" << location.get_language() << ";" << std::endl;
	os << "}" << std::endl;
	return os;
}
