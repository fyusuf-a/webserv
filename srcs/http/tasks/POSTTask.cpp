#include "POSTTask.hpp"
#include <unistd.h>
#include <cerrno>

POSTTask::POSTTask(int fd, ActiveHTTP& serv) : Task(fd, serv, WRITE), _head(0), _state(S_WAITING_FOR_MIDDLEWARES) {
	LOG.debug() << "New POST task (fd = " << _fd << ")" << std::endl;
}

POSTTask::~POSTTask(){}

bool POSTTask::on_readable(int) {
	return (true);
}

bool POSTTask::on_writable(int fd) {
	switch ((int)_state) {
		case S_WAITING_FOR_MIDDLEWARES:
			if (_serv.get_response().get_ready()) {
				_serv.write_beginning_on_write_buffer();
				_state = S_BEGINNING_WRITTEN;
			}
		break;
		case S_BEGINNING_WRITTEN:
			Request &request = _serv.get_request();
			std::string body = request.get_body();

			const char *str = body.c_str() + _head;

			ssize_t body_length = body.length() - _head;
			ssize_t write_length = BUFFER_LENGTH > body_length ? body_length : BUFFER_LENGTH;
			ssize_t ret = write(fd, str, write_length);
			_head += ret;

			if (ret == 0)
				return on_close(fd);
			else if (ret < 0)
			{
				_serv.get_response().set_code(Response::UnknownError);
				return on_close(fd);
			}
		break;
	}
	return (true);
}

bool POSTTask::always(int) {
	return (true);
}

bool	POSTTask::on_close(int) { 
	delete (this);
	return (false);
}
