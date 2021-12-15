#include "Request.hpp"

void								Request::set_over(bool over) {
	this->_over = over;
}

void								Request::set_path(std::string path) {
	this->_path = path;
}

void								Request::set_query(std::string query) {
	this->_query = query;
}

void								Request::set_extra_path(std::string extra_path) {
	this->_extra_path = extra_path;
}

void								Request::set_original_request_path(std::string original_path) {
	this->_original_request_path = original_path;
}

std::string	const&					Request::get_query(void) const {
	return this->_query;
}

std::string	const&					Request::get_extra_path(void) const {
	return this->_extra_path;
}

std::string const&					Request::get_method(void) const {
	return this->_method;
}

std::string const&					Request::get_path(void) const {
	return this->_path;
}

std::string const&					Request::get_original_request_path(void) const {
	return this->_original_request_path;
}

std::string const &					Request::get_protocol(void) const {
	return this->_protocol;
}

std::map<std::string, std::string>	const &Request::get_headers(void) const {
	return this->_headers;
}

std::string	const&					Request::get_body(void) const {
	return this->_body;
}

std::string	const&					Request::get_residual(void) const {
	return this->_residual;
}

int									Request::get_head(void) const {
	return this->_head;
}

bool								Request::get_over(void) const {
	return this->_over;
}

bool								Request::get_wrong(void) const {
	return this->_wrong;
}
bool								Request::get_is_script() const {
	return _is_script;
}

void 								Request::set_server(ServerBlock server){
	this->_server = server;
}
ServerBlock const 					&Request::get_server(void) const {
	return this->_server;
}

void 								Request::set_location(ServerLocation location){
	this->_location = location;
}
ServerLocation const 				&Request::get_location(void) const {
	return this->_location;
}

bool			Request::get_treated_by_middlewares(void) const {
	return this->_treated_by_middlewares;
}

void 			Request::set_treated_by_middlewares(bool treated_by_middlewares) {
	_treated_by_middlewares = treated_by_middlewares;
}

void			Request::set_is_script(bool set) {
	_is_script = set;
}


Request & 		Request::operator=( Request const & rhs ){
	if (this != &rhs) {
		this->_method = rhs.get_method();
		this->_path = rhs.get_path();
		this->_protocol = rhs.get_protocol();
		this->_headers = rhs.get_headers();
		this->_body = rhs.get_body();
		this->_head = rhs.get_head();
		this->_over = rhs.get_over();
		this->_to_read = rhs._to_read;
		this->_wrong= rhs._wrong;
		this->_treated_by_middlewares = rhs._treated_by_middlewares;
		this->_is_script = rhs._is_script;
		this->_original_request_path = rhs._original_request_path;
	}
	return *this;
}
Request::Request( Request const & src ) {
	*this = src;
}

void Request::reinitialize() {
	_method = "";
	_path = "";
	_protocol = "";
	_query = "";
	_extra_path = "";
	_original_request_path = "";
	_headers.clear();
	_body = "";
	_head = 0;
	_over = true;
	//_no_more_parsing = true;
	_residual = "";
	_field_name = "";
	_treated_by_middlewares = false;
	_is_script = false;
}

Request::Request() : _head(0), _over(true), _treated_by_middlewares(false), _is_script(false) {
}

Request::Request(std::string& buffer) : _head(0), _over(true), _treated_by_middlewares(false), _is_script(false) {
	this->parse(buffer);
}

Request::~Request() {
}

std::ostream& operator<<(std::ostream& os, const Request& req) {
       os << req.get_method() << " " << req.get_path() << " " << req.get_protocol() << "\r\n";
	   std::map<std::string, std::string> my_headers = req.get_headers();
       if (! my_headers.empty()) {
               for (std::map<std::string, std::string>::const_iterator it = my_headers.begin(); it != my_headers.end() ; it++) {
                       os << it->first << ": " << it->second << "\r\n";
               }
       }
       os << "\r\n" << req.get_body();
       //os << "over = " << (req.get_over() ? "true" : "false") << std::endl;
       /*os << "\r\n" << req.get_body();
       os << std::endl << "Other stuff:" << std::endl;
       os << "head = " << req.get_head() << std::endl;
       os << "over = " << (req.get_over() ? "true" : "false") << std::endl;
       os << "residual = \"" << req.get_residual() << "\"" << std::endl;*/
       return os;
}
