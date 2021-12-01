#include "POSTTask.hpp"
#include <unistd.h>
#include <cerrno>
Log &POSTTask::LOG = Log::getInstance();


POSTTask::POSTTask() : Callback() {
}

POSTTask::POSTTask(const POSTTask& src) : Callback(src) {
	*this = src;
}

POSTTask::POSTTask(int fd, ActiveHTTP *serv) : _serv(serv), _head(0){
	serv->get_response().set_delegated_to_task(true);
	NIOSelector::getInstance().add(fd, *this, WRITE);
}

POSTTask::~POSTTask(){}

bool POSTTask::on_readable(int) {
	return (true);
}

bool POSTTask::on_writable(int fd) {
	Request request = _serv->get_request();
	Response resp = _serv->get_response();
	std::string body = request.get_body();
	const char *str = body.c_str() + _head;

	ssize_t body_length = body.length() - _head;
	ssize_t write_length = BUFFER_LENGTH > body_length ? body_length : BUFFER_LENGTH;
	ssize_t ret = write(fd, str, write_length);

	_head += ret;
	if (ret == 0)
	{
		if (ret < 0)
			resp.set_code(Response::UnknownError);
		on_close(fd);
		return (false);
	}
	return (true);
}

bool POSTTask::always(int) {
	return (true);
}

bool	POSTTask::on_close(int fd) { 
	LOG.debug() << "Deleting the POSTTask" << std::endl;
    NIOSelector::getInstance().remove(fd);
   	close(fd);
	delete (this);
	return (false);
}
