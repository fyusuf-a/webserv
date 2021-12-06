#include "GETTask.hpp"
#include <unistd.h>


GETTask::GETTask() : Task() {
}

GETTask::GETTask(const GETTask& src) : Task(src) {
	*this = src;
}

GETTask::GETTask(int fd, ActiveHTTP *serv) : Task(fd, serv) {
}

GETTask::~GETTask(){}

bool GETTask::on_readable(int fd) {
	Response& resp = _serv->get_response();
	if (resp.get_beginning_written_on_write_buffer()) {
		std::string& write_buffer = _serv->get_write_buffer();
		char* tmp = _serv->get_tmp();
		ssize_t ret = read(fd, tmp, BUFFER_LENGTH);

		if (ret <= 0)
		{
			resp.set_written_on_write_buffer(true);
			on_close(fd);
			return (false);
		}
		write_buffer.append(tmp, ret);
	}
	return (true);
}

bool GETTask::on_writable(int) {
	return (true);
}

bool GETTask::always(int fd) {
	if (_serv->get_response().get_written_on_write_buffer()) {
		on_close(fd);
		return (false);
	}
	return (true);
}

bool	GETTask::on_close(int) { 
	delete (this);
	return (false);
}
