#include "Middlewares.hpp"

#define MYPATH ""

//405
void		MethodGET::body(ActiveHTTP& actHTTP, Request& request, Response& response, Middleware* next) {
	(void)response;
	(void)actHTTP;

    if (response.get_code() >= 400)
        next();
	else
	{
		if (_access_s(MYPATH.c_str(), 0) != 0)
			response.set_code(Response::NotFound);
		else if (_access_s(MYPATH.c_str(), 4) != 0)
			response.set_code(Response::Forbidden);
		else
		{
			std::string  body;
			std::string  result;

			std::ifstream fd(MYPATH.c_str());

			if (!fd.is_open() || !fd.good())
				response.set_code(Response::Forbidden);
			for (int i = 0; getline(fd, tmp); i++)
            {
                if (i)
                	body += '\n';
                body += tmp;
            }
			response.set_body(body);
		}

	}
	next();
}
