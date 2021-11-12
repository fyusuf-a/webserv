#include "Request.hpp"

/*void		Request::checkIncompleteRequest(std::string &buffer) const {
	(void)buffer;
	switch (this->get_head()) {
		case 5:
		case 4:
		case 3:
			if (_protocol != "HTTP/1.1")
				throw(505);
		//
		case 2:
			if (_path.find("\r\n") != std::string::npos)
				throw(400);
		//
		case 1:
			if (_method.find("\r\n") != std::string::npos)
				throw(501);
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
}*/
