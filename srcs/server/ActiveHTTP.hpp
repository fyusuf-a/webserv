#ifndef ACTIVEHTTP_HPP
#define ACTIVEHTTP_HPP

#include "Socket.hpp"
#include "NIOSelector.hpp"
#include "ActiveServer.hpp"
#include "../http/Request/Request.hpp"
#include <sstream>

class ActiveHTTP : public ActiveServer {

public:
	ActiveHTTP();
	ActiveHTTP(const ActiveHTTP&);
	ActiveHTTP(Socket*);
	ActiveHTTP& operator=(const ActiveHTTP&);
	virtual ~ActiveHTTP();
	Request _req;


protected:
	virtual void	readable(int fd);
};

#endif
