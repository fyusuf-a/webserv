#ifndef ACTIVESERVER_HPP
#define ACTIVESERVER_HPP

#include "Socket.hpp"
#include "NIOSelector.hpp"
#include "../defines.hpp"

class ActiveServer : public NIOSelector::Callback {

public:
	static Log& LOG;

	ActiveServer();
	/*ActiveServer(const ActiveServer&);*/
	ActiveServer(Socket*);
	//ActiveServer& operator=(const ActiveServer&);
	virtual ~ActiveServer();
	Socket			*getSocket() const;
	//std::string&	get_write_buffer();
	std::stringstream& get_write_stream();

protected:
	bool			_closing;
	//std::string		_write_buffer;
	//std::string		_read_buffer;
	std::stringstream	_write_stream;
	std::stringstream	_read_stream;
	Socket			*_socket;
	virtual bool	on_readable(int fd);
	virtual bool	on_writable(int fd);
	virtual bool	on_close(int fd);
	virtual bool	always(int fd);
};

#endif

