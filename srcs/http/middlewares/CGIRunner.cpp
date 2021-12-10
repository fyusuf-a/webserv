#include "Middleware.hpp"
#include <stdio.h>
#include <string>
#include <sys/wait.h>
#include <fcntl.h>
#define BUFFER_SIZE 1024

Log& CGIRunner::LOG = Log::getInstance();

void		CGIRunner::set_env(std::map<std::string, std::string>& env, ActiveHTTP const& server, Request const& request) {
	(void)server;
	std::map<std::string, std::string> headers = request.get_headers();
	std::map<std::string, std::string>::const_iterator it;
	std::ostringstream oss;
	
	// Todo: make headers case insensitive
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
	env["PATH_INFO"] = request.get_extra_path();

	// Setting PATH_TRANSLATED (same as SCRIPT_FILENAME?)
	env["PATH_TRANSLATED"] = env["PATH_INFO"].empty() ? "" : request.get_path();
	//env["PATH_TRANSLATED"] = env["PATH_INFO"].empty() ? "" : request.get_location().get_location_path() + env["PATH_INFO"];

	// Setting QUERY_STRING //Todo
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

	//INetAddress const& interface = server.getSocket()->getInterface();
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
	/*env["CHARSET"] = "utf-8";
	env["DOCUMENT_URI"] = "toto.php";
	env["DOCUMENT_ROOT"] = "toto.php";
	env["SCRIPT_FILENAME"] = "toto.php";
	env["ENCODING"] = "";
	env["HOST"] = "my_server";
	env["USER_AGENT"] = "Mozilla/5.0";
	env["PHP_SELF"] = "/toto.php";*/

}

void		CGIRunner::body(ActiveHTTP& server, Request& request, Response& response, MiddlewareChain& next) {
	(void)request;
	if (response.get_code() >= 400 || !request.get_is_script())
		return next();

	(void)server;
	std::map<std::string, std::string> env;
	set_env(env, server, request);

	char *env_tab[env.size() + 1];
	env_tab[env.size()] = 0;
	std::string tmp;
	int i = 0;
	for (std::map<std::string, std::string>::iterator it = env.begin(); it != env.end(); it++, i++) {
		tmp = it->first + "=" + it->second;
		env_tab[i] = new char[tmp.size() + 1];
		strcpy(env_tab[i], tmp.c_str());
	}

	//int status;
	std::string const& cgi_program_str = request.get_location().get_cgi_bin().c_str();
	char* cgi_program = new char [cgi_program_str.size() + 1];
	cgi_program = const_cast<char*>(cgi_program_str.c_str());
	char* cgi_script  = (char*)"toto.php";
	
	char* args[3];
	args[0] = cgi_program;
	args[1] = cgi_script;
	args[2] = 0;

	LOG.info() << "Launching \"" << args[0] << " " << args[1] <<  "\"" << std::endl;

	//int in_pipe[2];
	//int out_pipe[2];
	//pipe(in_pipe);
	//pipe(out_pipe);
	int pid = fork();
	if (pid == 0) {
		//close(in_pipe[1]);
		//close(out_pipe[0]);
		//dup2(in_pipe[0], 0);
		//dup2(out_pipe[1], 1);
		execve(args[0], args, env_tab);
		LOG.error() << "cgi binary \"" << request.get_location().get_cgi_bin() << "\" was not found on your system" << std::endl;
		exit(-1);
	}
	//close(in_pipe[0]);
	//close(out_pipe[1]);
	//NIOSelector::getInstance()->add(in_pipe[0], 
	for (size_t i = 0; i < env.size(); i++)
		delete env_tab[i];

	int status;
	waitpid(pid, &status, WUNTRACED);
	LOG.info() << cgi_script << " has stopped running" << std::endl;

	next();
}
