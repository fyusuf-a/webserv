#ifndef ACTIVEHTTP_HPP
#define ACTIVEHTTP_HPP

#include "Socket.hpp"
#include "NIOSelector.hpp"
#include "ActiveServer.hpp"
#include "../http/Request/Request.hpp"
#include "../http/Response/Response.hpp"
#include "../parsingConf/serverBlock.hpp"
#include <sstream>
#include <list>
#define TIMEOUT 60.0

class ActiveHTTP : public ActiveServer {

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
	void setServerBlocks(std::vector<ServerBlock> const*);
	time_t const& get_last_time_active() const;
	const std::list<Request>& get_reqs() const;
	std::list<Response>& get_resps();

protected:
	bool								_still_parsing;
	time_t								_last_time_active;
	INetAddress							_interface;
	std::vector<ServerBlock> const *	_server_blocks;
	std::list<Request>					_reqs;
	std::list<Response>					_resps;
	virtual bool						on_readable(int fd);
	virtual bool						always(int fd);
};

#endif
