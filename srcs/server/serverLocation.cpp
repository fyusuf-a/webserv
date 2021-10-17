#include "../../includes/serverLocation.hpp"


ServerLocation::ServerLocation() :
_cgi_ext(""), _cgi_bin(""), _language(""), _auto_index(""), _auth_basic("") , _auth_basic_file(""), _body_size(-1){}

ServerLocation::ServerLocation(const ServerLocation &other) :
_index(other._index), _methods(other._methods), _cgi_ext(other._cgi_ext),
_cgi_bin(other._cgi_ext), _language(other._language), _auto_index(other._auto_index),
_auth_basic(other._auth_basic) , _auth_basic_file(other._auth_basic_file), _body_size(other._body_size){}

ServerLocation::~ServerLocation(){}
    
ServerLocation &ServerLocation::operator=(const ServerLocation &other)
{
    if (this != &other)
        *this = other;
    return (*this);
}

void    ServerLocation::set_index(std::vector<std::string> const &index){ this->_index = index; }
void    ServerLocation::set_methods(std::vector<std::string> const &methods){ this->_methods = methods; }
void    ServerLocation::set_cgi_ext(std::string const &cgi_ext){ this->_cgi_ext = cgi_ext; }
void    ServerLocation::set_cgi_bin(std::string const &cgi_bin){ this->_cgi_bin = cgi_bin; }
void    ServerLocation::set_language(std::string const &language){ this->_language = language; }
void    ServerLocation::set_auto_index(std::string const &val){ this->_auto_index = val; }
void    ServerLocation::set_auth_basic(std::string const &val){this->_auth_basic = val; }
void    ServerLocation::set_auth_basic_file(std::string const &path){ this->_auth_basic_file = path; }
void    ServerLocation::set_body_size(int val){ this->_body_size = val; }

std::vector<std::string> const   &ServerLocation::get_index(void) const{ return (this->_index); }
std::vector<std::string> const   &ServerLocation::get_methods(void) const{ return (this->_methods); }
std::string const   &ServerLocation::get_cgi_ext(void) const{ return (this->_cgi_ext); }
std::string const   &ServerLocation::get_cgi_bin(void) const{ return (this->_cgi_bin); }
std::string const   &ServerLocation::get_language(void) const{ return (this->_language); }
std::string const   &ServerLocation::get_auto_index(void) const{ return (this->_auto_index); }
std::string const   &ServerLocation::get_auth_basic(void) const{ return (this->_auth_basic); }
std::string const   &ServerLocation::get_auth_basic_file(void) const{ return (this->_auth_basic_file); }
int                 ServerLocation::get_body_size(void) const{ return (this->_body_size); }

/*std::ostream& operator<<(std::ostream& os, const ServerLocation& location) {
	os << "index: " << std::endl;
	os <<  location.get_index() << std::endl;
}*/
