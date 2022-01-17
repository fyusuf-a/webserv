#include "Middleware.hpp"
#include <sstream>
#include <stdio.h>
#include <string>
#include "../tasks/GETTask.hpp"
#include <sys/types.h>
#include <dirent.h>

Log& MethodGET::LOG = Log::getInstance();

std::string replace_reserved(char *ptr) {
	std::size_t loc = -1;
	std::string reserved = "&<>\"";
	std::size_t it = 0;
	std::string replacement[4] = { "&amp", "&lt", "&gt", "&quot" };
	std::string str(ptr);
	
	while (it < 4) {
		loc = str.find(reserved[it], loc + 1);
		if (loc != std::string::npos)
			str.replace(loc, 1, replacement[it]);
		else {
			it++;
			loc = -1;
		}
	}
	return (str);
}

void		display_index(Request& request, Response& response) {
	std::ostringstream oss;
	DIR *dir;
    struct dirent *ent;
	struct stat s;    
	std::string file_path;
	std::string final_slash;

	oss << "<html>\n<head><title>Index of "
		<< request.get_original_request_path()
		<< "</title></head>\n<body>"
		<< "<pre>\n";

    if ((dir = opendir(request.get_path().c_str())) != NULL) {
      while ((ent = readdir(dir)) != NULL) {
      	file_path = request.get_path() + ent->d_name;
	    final_slash = "";
	    if (stat(file_path.c_str(), &s)) {
	    	response.set_code(Response::UnknownError);
	    	return ;
	    }
	    if (s.st_mode & S_IFDIR) {
	    	final_slash = "/";
	    }
		oss	<< "<a href=\"http://"
			<< request.get_server().get_server_conf().getName()
			<< request.get_original_request_path() << Utils::percent_encode(ent->d_name) << final_slash <<  "\">"
			<< replace_reserved(ent->d_name) << final_slash
			<< "</a>\n";
      }
      closedir(dir);
      oss << "</pre></body>";
    } 
    else {
      response.set_code(Response::NotFound);
      return ;
    }
	response.set_body(oss.str());
}

void		MethodGET::body(ActiveHTTP&serv, Request& request, Response& response, MiddlewareChain& next) {

	if (response.get_code() >= 400
		|| !(request.get_method() == "GET" || request.get_method() == "HEAD")
		|| request.get_is_script())
        return next();

    if (response.get_index_display()) {
    	display_index(request, response);
    	return next();
    }

	const char *filename = request.get_path().c_str();

	if (!Utils::is_file(filename) || access(filename, 0) != 0)
	{
		LOG.debug() << "Cannot find file " << filename << std::endl;
		response.set_code(Response::NotFound);
		return next();
	}
	if (access(filename, 4) != 0) {
		response.set_code(Response::Forbidden);
		return next();
	}
	std::string  body;
	std::string  result;

	//Get file size
	std::ifstream* file = new std::ifstream(filename, std::ios::binary);
	file->seekg(0, std::ios::end);
	ssize_t file_size = file->tellg();
	delete file;

	int  	fd;
	if ((fd = open(filename, O_RDONLY )) < 0) {
		response.set_code(Response::Forbidden);
		return next();
	}
	std::ostringstream os;

	os << file_size;

	response.delete_header("Transfer-Encoding");
	response.set_header("Content-Length", os.str());

	new GETTask(fd, serv);
	return next();
}
