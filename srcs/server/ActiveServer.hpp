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
	virtual void	readable(int fd);
	virtual void	writable(int fd);
	virtual void	on_close(int fd);
};

#endif
