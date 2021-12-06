#include "Task.hpp"

Log& Task::LOG = Log::getInstance();

Task::Task() : NIOSelector::Callback() {
}

Task::Task(const Task& src) : NIOSelector::Callback(src), _fd(src._fd), _serv(src._serv){
}

Task::Task(int fd, ActiveHTTP* serv) : _fd(fd), _serv(serv) {
	LOG.debug() << "New task (fd = " << _fd << ")" << std::endl;
	serv->set_ongoing_task(this);
	if (serv->get_request().get_method() == "GET")
		NIOSelector::getInstance().add(_fd, *this, READ);
	else if (serv->get_request().get_method() == "POST")
		NIOSelector::getInstance().add(_fd, *this, WRITE);
}

Task::~Task() {
	LOG.debug() << "Deleting task (fd = " << _fd << ")" << std::endl;
    NIOSelector::getInstance().remove(_fd);
	close(_fd);
	_serv->set_ongoing_task(NULL);
}
