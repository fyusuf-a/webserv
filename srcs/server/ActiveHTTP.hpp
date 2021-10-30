#ifndef ACTIVEHTTP_HPP
#define ACTIVEHTTP_HPP

#include "Socket.hpp"
#include "NIOSelector.hpp"
#include "ActiveServer.hpp"
#include "../http/Request/Request.hpp"
#include <sstream>
#define TIMEOUT 60.0

class ActiveHTTP : public ActiveServer {

public:
	ActiveHTTP();
	ActiveHTTP(const ActiveHTTP&);
	ActiveHTTP(Socket*);
	ActiveHTTP& operator=(const ActiveHTTP&);
	virtual ~ActiveHTTP();
	const Request& get_req() const;
	time_t const& get_last_time_active() const;


protected:
	time_t			_last_time_active;
	Request			_req;
	virtual bool	on_readable(int fd);
	virtual bool	always(int fd);
};

#endif
