#include "GETTask.hpp"
#include <unistd.h>

Log &GETTask::LOG = Log::getInstance();


GETTask::GETTask() : Callback() {
}

GETTask::GETTask(const GETTask& src) : Callback(src) {
	*this = src;
}

GETTask::GETTask(int fd, ActiveHTTP *serv, ssize_t file_size) : _serv(serv), _finished(false), _file_size(file_size) {
	serv->get_response().set_delegated_to_task(true);
	NIOSelector::getInstance().add(fd, *this, READ);
}

GETTask::~GETTask(){}

bool GETTask::on_readable(int fd) {
	Response resp = _serv->get_response();
	if (resp.get_beginning_sent()) {
		std::string& write_buffer = _serv->get_write_buffer();
		char* tmp = _serv->get_tmp();
		ssize_t ret = read(fd, tmp, BUFFER_LENGTH);
		if (ret <= 0)
		{
			resp.set_sent(true);
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
	//Response& resp = _serv->get_response();
	//if (resp.get_ready())
	//{
		//std::string& server_buffer = _serv->get_write_buffer();
		//server_buffer += _buffer;
		//_buffer = "";
	//}
	if (_serv->get_response().get_sent()) {
		LOG.debug() << "Deleting GETTask because the response is totally written on ActiveHTTP write buffer" << std::endl;
		on_close(fd);
		return (false);
	}
	return (true);
}

bool	GETTask::on_close(int fd) { 
	LOG.debug() << "Deleting the GETTask" << std::endl;
    NIOSelector::getInstance().remove(fd);
	delete (this);
	return (false);
}
