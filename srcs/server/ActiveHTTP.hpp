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
	//ActiveHTTP(const ActiveHTTP&);
	ActiveHTTP(Socket*);
	ActiveHTTP(Socket*, INetAddress const&, std::vector<ServerBlock> const*);
	//ActiveHTTP& operator=(const ActiveHTTP&);
	virtual ~ActiveHTTP();

	void add_response(const Response&);
	void write_all_on_write_buffer();
	void write_beginning_on_write_buffer();
	void launch_middleware_chain();
	//void send_partial_response(const std::string&);
	void postpone_timeout();

	void setServerBlocks(std::vector<ServerBlock> const*);
	//void set_ongoing_tasks(std::list<Task*> const& tasks);
	//void set_ongoing_task(Task*);
	void add_ongoing_task(Task* const&);
	void remove_ongoing_task(Task* const& task);

	uint16_t		get_original_port() const;
	INetAddress		getInterface() const;
	std::vector<ServerBlock> const*
					getServerBlocks() const;
	time_t const&	get_last_time_active() const;
	Request&		get_request();
	Response&		get_response();
	//std::string&	get_write_buffer();
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
	//Task*								_ongoing_task;
	std::list<Task*>					_ongoing_tasks;
	char								_tmp[BUFFER_LENGTH];
	virtual bool						on_readable(int fd);
	virtual bool						on_writable(int fd);
	virtual bool						on_close(int fd);
	virtual bool						always(int fd);
};

#endif
