#include "Middleware.hpp"
#include <cstddef>
#include <string>

Log& ExtractQueryAndExtension::LOG = Log::getInstance();

void		ExtractQueryAndExtension::body(ActiveHTTP&, Request& request, Response& response, MiddlewareChain& next) {

    if (response.get_code() >= 400){
        next();
        return ;
    }
    
    std::string path = request.get_path();
    std::size_t loc = path.find('?');
	std::string before_query = path.substr(0, loc);

	// Finding the extension of the file
	size_t last_point = before_query.find_last_of(".");
	if (last_point != std::string::npos)
	{
		std::string bad_extension = before_query.substr(last_point + 1);
		std::string extension;
		size_t last_char_of_extension = bad_extension.find_first_of("?;/");
		if (last_char_of_extension != std::string::npos)
			extension = bad_extension.substr(1, bad_extension.find_first_of("?;/") - 1);
		else
			extension = bad_extension;
		std::string mime_type;
		if ((mime_type = Utils::find_mime_type(extension)) != "")
			response.set_header("Content-Type", Utils::find_mime_type(extension), true);
	}
	// Setting path and query
	if (loc != std::string::npos) {
		request.set_query(path.substr(loc + 1));
		request.set_path(before_query);
	}

    next();
}
