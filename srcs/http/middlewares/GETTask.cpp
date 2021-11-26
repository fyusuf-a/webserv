#include "GETTask.hpp"

Log &GETTask::LOG = Log::getInstance();


GETTask::GETTask() : Callback() {
}

GETTask::GETTask(const GETTask& src) : Callback(src) {
	*this = src;
}

GETTask::GETTask(int fd, ActiveHTTP *serv) : _serv(serv), _finished(false) {
	serv->get_response().set_delegated_to_task(true);
	NIOSelector::getInstance().add(fd, *this, READ);
}

GETTask::~GETTask(){}

bool GETTask::on_readable(int fd) {
	static size_t bytes_sent = 0;
	Response resp = _serv->get_response();
	//if (resp.get_middleware_wrote_to_write_buffer()) {
	if (resp.get_beginning_sent()) {
		std::string& write_buffer = _serv->get_write_buffer();
		size_t buf_size = write_buffer.length();
		if (buf_size < BUFFER_LENGTH)
		{
			char* tmp = _serv->get_tmp();
			LOG.debug() << "Size to be read " << BUFFER_LENGTH - buf_size << std::endl;
			int ret = read(fd, tmp, BUFFER_LENGTH - buf_size);
			tmp[ret] = 0;
			if (ret <= 0)
			{
				resp.set_sent(true);
				if (ret == 0)
					LOG.debug() << "Deleting GETTask after reading 0 bytes" << std::endl;
				if (ret < 0)
					LOG.debug() << "Deleting GETTask after an error" << std::endl;
				on_close(fd);
				return (false);
			}
			write_buffer += tmp;
			bytes_sent += ret;
		}
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
