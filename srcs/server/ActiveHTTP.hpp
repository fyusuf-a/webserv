#ifndef ACTIVEHTTP_HPP
#define ACTIVEHTTP_HPP

#include "Socket.hpp"
#include "NIOSelector.hpp"
#include "ActiveServer.hpp"
#include "../http/Request/Request.hpp"
#include "../http/Response/Response.hpp"
#include "../parsingConf/serverBlock.hpp"
#include "../http/middlewares/MiddlewareChain.hpp"
#include <sstream>
#include <list>
#define TIMEOUT 60.0

class MiddlewareChain;

class ActiveHTTP : public ActiveServer {

private:
	bool check_timeout(int fd);

public:
	static Log& LOG;

	ActiveHTTP();
	ActiveHTTP(const ActiveHTTP&);
	ActiveHTTP(Socket*);
	ActiveHTTP(Socket*, INetAddress const&, std::vector<ServerBlock> const*);
	ActiveHTTP& operator=(const ActiveHTTP&);
	virtual ~ActiveHTTP();

	void add_response(const Response&);

	std::vector<ServerBlock> const* getServerBlocks() const;
	INetAddress getInterface() const;
	void setServerBlocks(std::vector<ServerBlock> const*);
	time_t const& get_last_time_active() const;
	Request& get_request();
	Response& get_response();
	void send_response();

protected:
	time_t								_last_time_active;
	INetAddress							_interface;
	std::vector<ServerBlock> const *	_server_blocks;
	Request								_request;
	Response							_response;
	MiddlewareChain						*_chain;
	virtual bool						on_readable(int fd);
	virtual bool						on_close(int fd);
	virtual bool						always(int fd);
};

#endif
