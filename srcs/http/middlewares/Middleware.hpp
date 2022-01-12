#ifndef MIDDLEWARE_HPP
# define MIDDLEWARE_HPP
# include <iostream>
# include "../Request/Request.hpp"
# include "../Response/Response.hpp"
# include "../../utils/Singleton.hpp"
# include "../../webserv/webserv.hpp"
# include "../../ipaddress/INetAddress.hpp"
# include "MiddlewareChain.hpp"
# include "../../server/ActiveHTTP.hpp"
# include "../../utils/Log.hpp"
# include "../../server/NIOSelector.hpp"

class MiddlewareChain;
class ActiveHTTP;

class Middleware
{
	public:
		Middleware();
		Middleware(ActiveHTTP& callback);
		Middleware(const Middleware& src);
		virtual ~Middleware();
		Middleware& operator=(const Middleware& src);

		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain&) = 0;
};

class CheckSyntax : public Middleware, public Singleton<CheckSyntax>
{
	public:
		CheckSyntax(){};
		virtual	~CheckSyntax() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain&);
};

class MethodChecker : public Middleware, public Singleton<MethodChecker>
{
	public:
		MethodChecker(){};
		virtual	~MethodChecker() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain&);
};

class IndexSelector : public Middleware, public Singleton<IndexSelector>
{
	public:
		static Log& LOG;
		IndexSelector(){};
		virtual	~IndexSelector() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain&);
};

class ExtractQuery : public Middleware, public Singleton<ExtractQuery>
{
	public:
		static Log& LOG;
		ExtractQuery(){};
		virtual	~ExtractQuery() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain&);
};

// Also manages HEAD requests
class MethodGET : public Middleware, public Singleton<MethodGET>
{
	public:
		static Log& LOG;
		MethodGET(){};
		virtual	~MethodGET() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain&);
};

class MethodDELETE : public Middleware, public Singleton<MethodDELETE>
{
	public:
		static Log& LOG;
		MethodDELETE(){};
		virtual	~MethodDELETE() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain&);
};

class MethodPOST : public Middleware, public Singleton<MethodPOST>
{
	public:
		static Log& LOG;
		MethodPOST(){};
		virtual	~MethodPOST() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain&);
};

class AbsolutePathConcatenator : public Middleware, public Singleton<AbsolutePathConcatenator>
{
	public:
		AbsolutePathConcatenator();
		virtual	~AbsolutePathConcatenator() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain&);
};

class Error : public Middleware, public Singleton<Error>
{
	public:
		Error(){};
		virtual	~Error() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain&);

};

// Also manages HEAD requests
class CGIRunner : public Middleware, public Singleton<CGIRunner>
{
	private:
		void set_env(Request::header_map& env, ActiveHTTP const& server,
				Request const& request);
		bool set_fd_as_non_blocking(int fd, char* fd_description);
		size_t size_of_header_map(const Request::header_map& map);
		void convert_map_to_tab(Request::header_map env, char** env_tab);

	public:
		static Log& LOG;
		CGIRunner(){};
		virtual	~CGIRunner() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};

class PathChopper : public Middleware, public Singleton<PathChopper>
{
	public:
		PathChopper() {};
		virtual	~PathChopper() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};

class Sender : public Middleware, public Singleton<Sender>
{
	public:
		static Log& LOG;
		Sender();
		virtual	~Sender() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain&);
};
 
std::string get_absolute_path(Request &request, const std::string &path);


#endif
