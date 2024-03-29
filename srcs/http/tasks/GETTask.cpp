#include "GETTask.hpp"
#include <unistd.h>


GETTask::GETTask(int fd, ActiveHTTP &serv) : Task(fd, serv, READ), _state(S_WRITING_BEGINNING) {
	LOG.debug() << "New GET task (fd = " << _fd << ")" << std::endl;
}

GETTask::~GETTask(){}

bool GETTask::on_readable(int fd) {
	if (_state == S_WRITING_BEGINNING) {
		_serv.write_beginning_on_write_buffer(fd);
		if (_serv.get_request().get_method() == "HEAD")
			return on_close(fd);
		_state = S_BEGINNING_WRITTEN;
	}
	char* tmp = _serv.get_tmp();
	ssize_t ret = read(fd, tmp, BUFFER_LENGTH);

	if (ret == 0)
		return on_close(fd);
	else if (ret < 0) {
		_serv.get_response().set_code(Response::UnknownError);
		return on_close(fd);
	}
	_serv.get_write_buffer().append(tmp, ret);
	return (true);
}

bool GETTask::on_writable(int) {
	return (true);
}

bool GETTask::always(int) {
	return (true);
}

bool	GETTask::on_close(int) { 
	delete (this);
	return (false);
}
