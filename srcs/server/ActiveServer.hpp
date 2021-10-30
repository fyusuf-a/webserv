#ifndef ACTIVESERVER_HPP
#define ACTIVESERVER_HPP

#define BUFFER_LENGTH 4096

#include "Socket.hpp"
#include "NIOSelector.hpp"

class ActiveServer : public NIOSelector::Callback {

public:
	ActiveServer();
	ActiveServer(const ActiveServer&);
	ActiveServer(Socket*);
	ActiveServer& operator=(const ActiveServer&);
	virtual ~ActiveServer();
	Socket			*getSocket();

protected:
	std::string		_write_buffer;
	std::string		_read_buffer;
	Socket			*_socket;
	virtual bool	on_readable(int fd);
	virtual bool	on_writable(int fd);
	virtual bool	on_close(int fd);
	virtual bool	always(int fd) = 0;
};

#endif

