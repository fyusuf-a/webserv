#include "Task.hpp"

Log& Task::LOG = Log::getInstance();

//Task::Task() : NIOSelector::Callback() {
//}

//Task::Task(const Task& src) : NIOSelector::Callback(src), _fd(src._fd), _serv(src._serv){
//}

Task::Task(int fd, ActiveHTTP& serv, short mode) : _fd(fd), _serv(serv) {
	serv.add_ongoing_task(this);
	NIOSelector::getInstance().add(_fd, *this, mode);
}

Task::~Task() {
	LOG.debug() << "Deleting task (fd = " << _fd << ")" << std::endl;
    NIOSelector::getInstance().remove(_fd);
	close(_fd);
	_serv.remove_ongoing_task(this);
	if (_serv.get_ongoing_tasks().empty())
		_serv.reinitialize(_fd);
	// Re-establish the read operations on the socket
	NIOSelector::getInstance().updateOps(_serv.getSocket()->getFd(), READ | WRITE);
}

int Task::get_fd() const {
	return _fd;
}
