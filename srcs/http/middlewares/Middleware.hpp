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

		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next) = 0;
};

class CheckSyntax : public Middleware, public Singleton<CheckSyntax>
{
	public:
		CheckSyntax();
		virtual	~CheckSyntax() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};

class BlockSelector : public Middleware, public Singleton<BlockSelector>
{
	public:
		BlockSelector();
		virtual	~BlockSelector() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};

class MethodChecker : public Middleware, public Singleton<MethodChecker>
{
	public:
		MethodChecker();
		virtual	~MethodChecker() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};

class IndexSelector : public Middleware, public Singleton<IndexSelector>
{
	public:
		IndexSelector(){};
		virtual	~IndexSelector() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};

class MethodGET : public Middleware, public Singleton<MethodGET>
{
	public:
		MethodGET();
		virtual	~MethodGET() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};

class MethodDELETE : public Middleware, public Singleton<MethodDELETE>
{
	public:
		MethodDELETE();
		virtual	~MethodDELETE() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};

class MethodPOST : public Middleware, public Singleton<MethodPOST>
{
	public:
		MethodPOST();
		virtual	~MethodPOST() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};

class AbsolutePathConcatenator : public Middleware, public Singleton<AbsolutePathConcatenator>
{
	public:
		AbsolutePathConcatenator();
		virtual	~AbsolutePathConcatenator() {};
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);
};

class CGIRunner : public Middleware, public Singleton<CGIRunner>
{
	private:
		void set_env(std::map<std::string, std::string>& env
							, ActiveHTTP const& server, Request const& request);
		void convert_map_to_tab(std::map<std::string, std::string>env
															, char** env_tab);

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
		virtual void	body(ActiveHTTP&, Request&, Response&, MiddlewareChain& next);

	private:
		void write_all_on_write_buffer(ActiveHTTP& serv, Response& response,
													std::ostringstream& oss);
		void add_content_length(Response& response, std::ostringstream& oss);
};
 
std::string get_absolute_path(Request &request, const std::string &path);


#endif
