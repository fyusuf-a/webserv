#include "Task.hpp"

Log& Task::LOG = Log::getInstance();

//Task::Task() : NIOSelector::Callback() {
//}

//Task::Task(const Task& src) : NIOSelector::Callback(src), _fd(src._fd), _serv(src._serv){
//}

Task::Task(int fd, ActiveHTTP& serv, short mode) : _fd(fd), _serv(serv) {
	LOG.debug() << "New task (fd = " << _fd << ")" << std::endl;
	serv.set_delegation_to_task(true);
	serv.add_ongoing_task(this);
	NIOSelector::getInstance().add(_fd, *this, mode);
}

Task::~Task() {
	LOG.debug() << "Deleting task (fd = " << _fd << ")" << std::endl;
    NIOSelector::getInstance().remove(_fd);
	close(_fd);
	_serv.remove_ongoing_task(this);
	_serv.reinitialize();
}
