#include "Middlewares.hpp"

//405
void		MethodsCheker::body(Request & request, Response & response, ServerBlocks const &serverBlocks, INetAddress const &interface) {


	(void)response;
	(void)interface;
	(void)serverBlocks;

	bool set = false;

	for (std::vector<std::string>::const_iterator it = request.get_location().get_methods().begin(); it != request.get_location().get_methods().end(); it++)
	{
		if (*it == request.get_method())
			set = true;
	}

	if (set == false)
		throw (405);
}
