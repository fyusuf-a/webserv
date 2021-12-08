#include "POSTTask.hpp"
#include <unistd.h>
#include <cerrno>


POSTTask::POSTTask() : Task(), _head(0) {
}

POSTTask::POSTTask(const POSTTask& src) : Task(src), _head(0) {
	*this = src;
}

POSTTask::POSTTask(int fd, ActiveHTTP *serv) : Task(fd, serv, WRITE), _head(0) {
}

POSTTask::~POSTTask(){}

bool POSTTask::on_readable(int) {
	return (true);
}

bool POSTTask::on_writable(int fd) {


	Request &request = _serv->get_request();
	
	Response &resp = _serv->get_response();


	std::string body = request.get_body();

	const char *str = body.c_str() + _head;

	ssize_t body_length = body.length() - _head;
	ssize_t write_length = BUFFER_LENGTH > body_length ? body_length : BUFFER_LENGTH;
	ssize_t ret = write(fd, str, write_length);

	_head += ret;

	if (ret == 0)
	{
		resp.set_written_on_write_buffer(true);
		return on_close(fd);
	}
	if (ret < 0)
	{
		resp.set_code(Response::UnknownError);
		return on_close(fd);
	}
	return (true);
}

bool POSTTask::always(int fd) {
	if (_serv->get_response().get_written_on_write_buffer()) {
			on_close(fd);
		return (false);
	}
	return (true);
}

bool	POSTTask::on_close(int) { 
	delete (this);
	return (false);
}
