#include "Request.hpp"

void								Request::set_over(bool over) {
	this->_over = over;
}

void								Request::set_path(const std::string& path) {
	_path = path;
}

void								Request::set_query(const std::string& query) {
	_query = query;
}

void								Request::set_extra_path(const std::string& extra_path) {
	_extra_path = extra_path;
}

void								Request::set_original_request_path(const std::string& original_path) {
	_original_request_path = original_path;
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
	return _path;
}

std::string const&					Request::get_original_request_path(void) const {
	return this->_original_request_path;
}

std::string const &					Request::get_protocol(void) const {
	return this->_protocol;
}

Request::header_map	const& Request::get_headers(void) const {
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

bool								Request::get_is_script() const {
	return _is_script;
}

bool								Request::get_wrong(void) const {
	return this->_wrong;
}

bool								Request::get_too_big_body(void) const {
	return this->_too_big_body;
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
ServerLocation 							&Request::get_location(void) {
	return this->_location;
}

void									Request::set_method(std::string method)
{
	this->_method = method;
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
		_method = rhs._method;
		_path = rhs._path;
		_original_request_path = rhs._original_request_path;
		_protocol = rhs._protocol;
		_headers = rhs._headers;
		_body = rhs._body;
		_head = rhs._head;
		_over = rhs._over;
		_wrong= rhs._wrong;
		_too_big_body= rhs._too_big_body;
		_last_zero_read = rhs._last_zero_read;
		_residual = rhs._residual;
		_field_name = rhs._field_name;
		_lctr = rhs._lctr;
		_treated_by_middlewares = rhs._treated_by_middlewares;
		_extra_path = rhs._extra_path;
		_query = rhs._query;
		_is_script = rhs._is_script;
		_to_read = rhs._to_read;
		_file_extension = rhs._file_extension;
	}
	return *this;
}
Request::Request( Request const & src ) {
	*this = src;
}

Request::Request()
	: _head(0)
	, _over(true)
	, _wrong(false)
	, _too_big_body(false)
	, _last_zero_read(false)
	, _lctr(0)
	, _treated_by_middlewares(false)
	, _is_script(false)
	, _to_read(0)
{
}

Request::~Request() {
}

std::ostream& operator<(std::ostream& os, Request const& req) {
	os << req.get_method() << " " << req.get_path() << " " << req.get_protocol() << "\r\n";
	os << req.get_headers();
	os << "\r\n";
	return os;
}

std::ostream& operator<<(std::ostream& os, Request const& req) {
	   os < req;
	   os << req.get_body();
       return os;
}
