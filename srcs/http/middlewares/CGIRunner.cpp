#include "Middleware.hpp"
#include <stdio.h>
#include <string>
#include <sys/wait.h>
#include <fcntl.h>
#include "../tasks/CGIOutTask.hpp"
#include "../tasks/POSTTask.hpp"

Log& CGIRunner::LOG = Log::getInstance();

void		CGIRunner::set_env(std::map<std::string, std::string>& env, ActiveHTTP const& server, Request const& request) {
	(void)server;
	Request::header_map const& headers = request.get_headers();
	Request::header_map::const_iterator it;
	std::ostringstream oss;
	
	// Setting AUTH_TYPE
	env["AUTH_TYPE"] = "";

	// Setting CONTENT_LENGTH
	it = headers.find("Content-Length");
	if (it == headers.end()) {
		ssize_t size = request.get_body().length();
		if (size != 0) {
			oss << request.get_body().length();
			env["CONTENT_LENGTH"] = oss.str();
			oss.str("");
		}
		else
			env["CONTENT_LENGTH"] = "";
	}
	else
		env["CONTENT_LENGTH"] = it->second;

	// Setting CONTENT_TYPE
	it = headers.find("Content-Type");
	env["CONTENT_TYPE"] = it == headers.end() ? "application/octet-stream" : it->second;

	// Setting GATEWAY_INTERFACE
	env["GATEWAY_INTERFACE"] = "CGI/1.1";

	// Setting PATH_INFO
#ifdef TEST42
	// The test CGI executable from 42 does not follow RFC's rules
	env["PATH_INFO"] = request.get_original_request_path();
#else
	env["PATH_INFO"] = request.get_extra_path();
#endif

	// Setting PATH_TRANSLATED (same as SCRIPT_FILENAME?)
	env["PATH_TRANSLATED"] = env["PATH_INFO"].empty() ? "" : request.get_path();

	// Setting QUERY_STRING
	env["QUERY_STRING"] = request.get_query();

	// Setting REMOTE_ADDR
	INetAddress* peer = server.getSocket()->getPeer();
	oss << peer->getAddress();
	env["REMOTE_ADDR"] = peer ? oss.str() : "0.0.0.0";
	oss.str("");

	// Setting REMOTE_HOST
	env["REMOTE_HOST"] = "";

	// Setting REQUEST_METHOD
	env["REQUEST_METHOD"] = request.get_method();

	// Setting SCRIPT_NAME (path from the URI)
	env["SCRIPT_NAME"] = request.get_original_request_path();

	// Setting SCRIPT_FILENAME (path executed at the server)
	env["SCRIPT_FILENAME"] = request.get_path();

	// Setting SERVER_NAME
	oss << request.get_server().get_server_conf().getName();
	env["SERVER_NAME"] = oss.str();
	oss.str("");

	// Setting SERVER_PORT
	oss << server.get_original_port();
	env["SERVER_PORT"] = oss.str();
	oss.str("");

	env["SERVER_PROTOCOL"] = SERVER_PROTOCOL;

	// For PHP CGI which throws a tantrum if this environment variable is unset
	env["REDIRECT_STATUS"] = "200";

	// For the 42 test CGI executable which throws a tantrum if this environment variable is unset
#ifdef TEST42
	env["REQUEST_URI"] = request.get_original_request_path();
#endif
}

void CGIRunner::convert_map_to_tab(std::map<std::string, std::string>env
															, char** env_tab) {
	env_tab[env.size()] = 0;
	std::string tmp;
	int i = 0;
	for (std::map<std::string, std::string>::iterator it = env.begin()
												; it != env.end(); it++, i++) {
		tmp = it->first + "=" + it->second;
		env_tab[i] = new char[tmp.size() + 1];
		strcpy(env_tab[i], tmp.c_str());
	}
}

void		CGIRunner::body(ActiveHTTP& server, Request& request
								, Response& response, MiddlewareChain& next) {
	if (response.get_code() >= 400 || !request.get_is_script())
		return next();

	std::map<std::string, std::string> env;
	set_env(env, server, request);
	char *env_tab[env.size() + 1];
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
	for (size_t i = 0; i < env.size(); i++)
		delete env_tab[i];

	next();
}
