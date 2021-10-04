#include "Middlewares
.hpp"

void		CheckSyntax::body(Config & config, Request & resquest, IMiddlewares *next) {
	std::string met = _fields.get_method();
	if (met != "GET" && met != "POST" && met != "DELETE")
		throw(501);

	if (_fields.get_path()[0] != '/')
		throw(400);

	if (_fields.get_protocol() != "HTTP/1.1")
		throw(505);

	if (check_header())
		throw(400);

}