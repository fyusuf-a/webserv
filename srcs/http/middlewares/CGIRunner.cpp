#include "Middleware.hpp"
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <sys/wait.h>
#include <fcntl.h>
#include "../tasks/CGIOutTask.hpp"
#include "../tasks/POSTTask.hpp"

Log& CGIRunner::LOG = Log::getInstance();

void		CGIRunner::set_env(Request::header_map& env, ActiveHTTP const& server, Request const& request) {
	(void)server;
	Request::header_map const& headers = request.get_headers();
	Request::header_map::const_iterator it;
	std::ostringstream oss;
	
	// Setting AUTH_TYPE
	env["AUTH_TYPE"].push_front("");

	// Setting CONTENT_LENGTH
	it = headers.find("Content-Length");
	if (it == headers.end()) {
		ssize_t size = request.get_body().length();
		if (size != 0) {
			oss << request.get_body().length();
			env["CONTENT_LENGTH"].push_front(oss.str());
			oss.str("");
		}
		else
			env["CONTENT_LENGTH"].push_front("");
	}
	else
		env["CONTENT_LENGTH"] = it->second;

	// Setting CONTENT_TYPE
	it = headers.find("Content-Type");
	if (it == headers.end())
		env["CONTENT_TYPE"].push_front("application/octet-stream");
	else {
		try {
			 env["CONTENT_TYPE"].push_front(it->second.front());
		}
		catch(std::out_of_range& e) {
		}
	}

	// Setting GATEWAY_INTERFACE
	env["GATEWAY_INTERFACE"].push_front("CGI/1.1");

	// Setting PATH_INFO
#ifdef TEST42
	// The test CGI executable from 42 does not follow RFC's rules
	env["PATH_INFO"].push_front(request.get_original_request_path());
#else
	env["PATH_INFO"].push_front(request.get_extra_path());
#endif
	LOG.debug() << "PATH_INFO = \"" << list_front(env["PATH_INFO"]) << '\"' << std::endl; 

	// Setting PATH_TRANSLATED (same as SCRIPT_FILENAME?)
	env["PATH_TRANSLATED"].push_front(env["PATH_INFO"].empty() ?
													"" : request.get_path());

	// Setting QUERY_STRING
	env["QUERY_STRING"].push_front(request.get_query());

	// Setting REMOTE_ADDR
	INetAddress* peer = server.getSocket()->getPeer();
	oss << peer->getAddress();
	env["REMOTE_ADDR"].push_front(peer ? oss.str() : "0.0.0.0");
	oss.str("");

	// Setting REMOTE_HOST
	env["REMOTE_HOST"].push_front("");

	// Setting REQUEST_METHOD
	env["REQUEST_METHOD"].push_front(request.get_method());

	// Setting SCRIPT_NAME (path from the URI)
	env["SCRIPT_NAME"].push_back(request.get_original_request_path());

	// Setting SCRIPT_FILENAME (path executed at the server)
	env["SCRIPT_FILENAME"].push_front(request.get_path());

	// Setting SERVER_NAME
	oss << request.get_server().get_server_conf().getName();
	env["SERVER_NAME"].push_front(oss.str());
	oss.str("");

	// Setting SERVER_PORT
	oss << server.get_original_port();
	env["SERVER_PORT"].push_front(oss.str());
	oss.str("");

	env["SERVER_PROTOCOL"].push_front(SERVER_PROTOCOL);

	// For PHP CGI which throws a tantrum if this environment variable is unset
	env["REDIRECT_STATUS"].push_front("200");

	// For the 42 test CGI executable which throws a tantrum if this environment variable is unset
#ifdef TEST42
	env["REQUEST_URI"].push_front(request.get_original_request_path());
#endif

	// Adding headers from the request
	Request::header_map::iterator jt;
	for (Request::header_map::const_iterator it = headers.begin();
			it != headers.end(); it++) {
		std::string header_name = it->first;
		// See RFC3875, section 4.1.18.
		for (size_t i = 0; i < header_name.size(); i++) {
			if (header_name[i] == '-') {
				header_name[i] = '_';
				continue;
			}
			header_name[i] = std::toupper(header_name[i]);
		}
		jt = env.find(header_name);
		if (jt == env.end())
			env["HTTP_" + header_name] = it->second;
	}
}

size_t CGIRunner::size_of_header_map(const Request::header_map& map) {
	size_t ret = 0;
	for (Request::header_map::const_iterator it = map.begin(); it != map.end();
			it++) {
		ret += it->second.size();
	}
	return ret;
}

void CGIRunner::convert_map_to_tab(Request::header_map env , char** env_tab) {
	env_tab[size_of_header_map(env)] = 0;
	std::string tmp;
	size_t i = 0;
	for (Request::header_map::iterator it = env.begin()
												; it != env.end(); it++) {
		for (std::list<std::string>::const_iterator jt = it->second.begin();
					jt != it->second.end(); jt++, i++) {
			//tmp = it->first + "=" + it->second;
			tmp = it->first + "=" + *jt;
			env_tab[i] = new char[tmp.size() + 1];
			strcpy(env_tab[i], tmp.c_str());
		}
	}
}

void		CGIRunner::body(ActiveHTTP& server, Request& request
								, Response& response, MiddlewareChain& next) {
	if (response.get_code() >= 400 || response.get_code() == 301 || !request.get_is_script())
		return next();

	Request::header_map env;
	set_env(env, server, request);
	char *env_tab[size_of_header_map(env) + 1];
	convert_map_to_tab(env, env_tab);

	std::string const& cgi_program =
								request.get_location().get_cgi_bin().c_str();
	
	char* args[3];
	args[0] = (char*)cgi_program.c_str();
	args[1] = (char*)request.get_path().c_str();
	args[2] = 0;

	LOG.info() << "Launching \"" << args[0] << " " << args[1] <<  "\"" << std::endl;

	int in_pipe[2];
	int out_pipe[2];
	pipe(in_pipe);
	pipe(out_pipe);
	if (!Utils::set_fd_as_non_blocking(in_pipe[0], "in-pipe read extremity")
		|| !Utils::set_fd_as_non_blocking(in_pipe[1], "in-pipe write extremity")
		|| !Utils::set_fd_as_non_blocking(out_pipe[0], "out-pipe read extremity"))
		//|| !Utils::set_fd_as_non_blocking(out_pipe[1], "out-pipe write extremity"))
	{
		close(in_pipe[0]);
		close(in_pipe[1]);
		close(out_pipe[0]);
		close(out_pipe[1]);
		return next();
	}
	int pid = fork();
	if (pid == 0) {
		close(in_pipe[1]);
		close(out_pipe[0]);
		dup2(in_pipe[0], 0);
		dup2(out_pipe[1], 1);
		execve(args[0], args, env_tab);
		LOG.error() << "cgi binary \"" << request.get_location().get_cgi_bin() << "\" was not found on your system" << std::endl;
		exit(-1);
	}
	close(in_pipe[0]);
	close(out_pipe[1]);

	new POSTTask(in_pipe[1], server, POSTTask::NO_WRITE_ON_WRITE_BUFFER);
	new CGIOutTask(out_pipe[0], server, pid);
	for (size_t i = 0; i < size_of_header_map(env); i++)
		delete env_tab[i];
	next();
}
