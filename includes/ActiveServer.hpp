#ifndef ACTIVESERVER_HPPPP
#define ACTIVESERVER_HPPPP

#include "ActiveSocket.hpp"

class ActiveServer {

    public:
	ActiveServer();
	ActiveServer(const ActiveServer&);
	ActiveServer& operator=(const ActiveServer&);
	virtual ~ActiveServer();

    protected:
	ActiveSocket	*_socket;
	virtual void	readable(int fd);
	virtual void	writable(int fd);
	virtual void	on_close(int fd);

protected:
	std::string	_write_buffer;
	std::string	_read_buffer;
};

#endif

