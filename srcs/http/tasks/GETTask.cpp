#include "GETTask.hpp"
#include <unistd.h>


GETTask::GETTask(int fd, ActiveHTTP &serv) : Task(fd, serv, READ), _state(S_WAITING_FOR_MIDDLEWARES) {
}

GETTask::~GETTask(){}

bool GETTask::on_readable(int fd) {
	switch ((int)_state) {
		case S_WAITING_FOR_MIDDLEWARES:
			if (_serv.get_response().get_ready()) {
				_serv.write_beginning_on_write_buffer();
				_state = S_BEGINNING_WRITTEN;
			}
		break;
		case S_BEGINNING_WRITTEN:
			char* tmp = _serv.get_tmp();
			ssize_t ret = read(fd, tmp, BUFFER_LENGTH);

			if (ret == 0)
				return on_close(fd);
			else if (ret < 0) {
				_serv.get_response().set_code(Response::UnknownError);
				return on_close(fd);
			}
			_serv.get_write_buffer().append(tmp, ret);
		break;
	}
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
