#include "Middleware.hpp"
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#define BUFFER_SIZE 1024

Log& CGIRunner::LOG = Log::getInstance();

//405
void		CGIRunner::body(ActiveHTTP& server, Request& request, Response& response, MiddlewareChain& next) {
	(void)request;
	if (response.get_code() >= 400)
		next();

	(void)server;
	std::map<std::string, std::string> env;
	env["HTTP_AUTH_TYPE"] = "";
	env["HTTP_CONTENT_LENGTH"] = "10";
	env["HTTP_ACCEPT"] = "text/html";
	env["HTTP_CONTENT_TYPE"] = "text/html";
	env["HTTP_CHARSET"] = "utf-8";
	env["HTTP_PATH_INFO"] = "utf-8";
	env["HTTP_PATH_TRANSLATED"] = "";
	env["HTTP_QUERY_STRING"] = "lol=toto&toto=fill";
	env["HTTP_GATEWAY_INTERFACE"] = "CGI/1.1";
	//env["HTTP_ENCODING"] = "";
	env["HTTP_HOST"] = "my_server";
	env["HTTP_USER_AGENT"] = "Mozilla/5.0";

	char *env_tab[env.size() + 1];
	env_tab[env.size()] = 0;
	std::string tmp;
	int i = 0;
	for (std::map<std::string, std::string>::iterator it = env.begin(); it != env.end(); it++, i++) {
		tmp = it->first + "=" + it->second;
		//env_tab[i] = (char*)malloc(tmp.size() + 1);
		env_tab[i] = new char[tmp.size() + 1];
		strcpy(env_tab[i], tmp.c_str()); }

	//int status;
	char* cgi_program  = (char*)"toto.php";
	LOG.info() << "Launching php-cgi " << cgi_program << std::endl;
	char *args[] = {(char*)"/usr/bin/php-cgi", cgi_program, 0};

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
		exit(1);
	}
	close(in_pipe[0]);
	close(out_pipe[1]);
	//NIOSelector::getInstance()->add(in_pipe[0], 
	LOG.info() << cgi_program << " has stopped running" << std::endl;

	for (size_t i = 0; i < env.size(); i++)
		delete env_tab[i];

	next();
}
