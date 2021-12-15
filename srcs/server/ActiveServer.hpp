#ifndef ACTIVESERVER_HPP
#define ACTIVESERVER_HPP

#include "Socket.hpp"
#include "NIOSelector.hpp"
#include "../defines.hpp"


class ActiveServer : public NIOSelector::Callback {

public:
	static Log& LOG;

	ActiveServer();
	ActiveServer(const ActiveServer&);
	ActiveServer(Socket*);
	ActiveServer& operator=(const ActiveServer&);
	virtual ~ActiveServer();
	Socket			*getSocket() const;

protected:
	std::string		_write_buffer;
	std::string		_read_buffer;
	Socket			*_socket;
	virtual bool	on_readable(int fd);
	virtual bool	on_writable(int fd);
	virtual bool	on_close(int fd);
	virtual bool	always(int fd);
};

#endif
