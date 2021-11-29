#include "POSTTask.hpp"
#include <unistd.h>

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

	std::cout << "test " << request.get_body() << std::endl;
	ssize_t ret = write(fd, request.get_body().c_str() + _head, BUFFER_LENGTH);
	_head += ret;
	if (ret <= 0)
	{
		resp.set_sent(true);
		on_close(fd);
		return (false);
	}
	return (true);
}

bool POSTTask::always(int fd) {
	if (_serv->get_response().get_sent()) {
		LOG.debug() << "Deleting GETTask because the response is totally written on ActiveHTTP write buffer" << std::endl;
		on_close(fd);
		return (false);
	}
	return (true);
}

bool	POSTTask::on_close(int fd) { 
	LOG.debug() << "Deleting the POSTTask" << std::endl;
    NIOSelector::getInstance().remove(fd);
	delete (this);
	return (false);
}
