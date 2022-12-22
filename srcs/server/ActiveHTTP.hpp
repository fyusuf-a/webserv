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
class Task;

class ActiveHTTP : public ActiveServer {

private:
	bool check_timeout(int fd);

public:
	static Log& LOG;

	ActiveHTTP();
	ActiveHTTP(Socket*);
	ActiveHTTP(Socket*, INetAddress const&, std::vector<ServerBlock> const*);
	virtual ~ActiveHTTP();

	void write_beginning_on_write_buffer(int fd);
	void launch_middleware_chain(int fd);
	void postpone_timeout();
	bool reinitialize(int fd);
	void add_content_length(std::ostringstream& oss);

	void set_chain(MiddlewareChain* const&);
	void add_ongoing_task(Task* const&);
	void remove_ongoing_task(Task* const& task);

	uint16_t		get_original_port() const;
	INetAddress		get_interface() const;
	std::vector<ServerBlock> const* get_server_blocks() const;
	time_t const&	get_last_time_active() const;
	Request&		get_request();
	Response&		get_response();
	std::string&	get_write_buffer();
	char*			get_tmp();
	std::list<Task*> const& get_ongoing_tasks() const;

protected:
	uint16_t							_original_port;
	time_t								_last_time_active;
	INetAddress							_interface;
	std::vector<ServerBlock> const*		_server_blocks;
	Request								_request;
	Response							_response;
	MiddlewareChain*					_chain;
	// If a task is launched, it is responsible for writing the response to the
	// ActiveHTTP write buffer, otherwise, it is written by the middleware
	// called Sender
	std::list<Task*>					_ongoing_tasks;
	char								_tmp[BUFFER_LENGTH];

	virtual bool						on_readable(int fd);
	virtual bool						on_writable(int fd);
	virtual bool						on_close(int fd);
	virtual bool						always(int fd);
};

#endif
