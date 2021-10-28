#include "Request.hpp"

void		Request::checkIncompleteRequest(void) const {
	switch (this->get_head()) {
		case 5:
		break;
		case 4:
		break;
		case 3:
			if (_protocol != "HTTP/1.1")
				throw(505);
		break;
		case 2:
			if (_path[0] != '/')
				throw(400);
		break;
		case 1:
			if (_method != "GET" && _method != "POST" && _method != "DELETE")
				throw(501);
		break;
	}

	if (_residual == "")
		return ;

	std::string http = "HTTP/1.1";
	std::string get = "GET";
	std::string post = "POST";
	std::string del = "DELETE";

	switch (this->get_head()) {
		case 2:
			if (http.find(_residual) == std::string::npos)
				throw(505);
			break;
		case 1:
			if ( _residual[0] != '/')
				throw(400);
			break;
		case 0:
			if (get.find(_residual) == std::string::npos &&
				post.find(_residual) == std::string::npos &&
				del.find(_residual) == std::string::npos)
				throw(501);
			break;
	}
}
