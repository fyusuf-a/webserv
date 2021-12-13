#include "CGITask.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


CGITask::CGITask(int fd, ActiveHTTP& serv, int pid)
		: Task(fd, serv, READ)
		, _state(S_HEADER_NAME)
		, _index(0)
		, _pid(pid) {
	_buffer = new std::string();
}

CGITask::~CGITask(){
	if (_buffer != &_serv.get_write_buffer())
		delete _buffer;
}

bool CGITask::on_readable(int fd) {
	Response& response = _serv.get_response();

	if (_state == S_WAITING_FOR_MIDDLEWARES) {
		if (_serv.get_response().get_ready())
			_state = S_HEADER_NAME;
		else
			return true;
	}

	// Read from the pipe
	char* tmp = _serv.get_tmp();
	ssize_t ret = read(fd, tmp, BUFFER_LENGTH);

	int status;
	// If no data is read from the pipe, harvest the zombie and delete the task
	if (ret <= 0)
	{
		waitpid(_pid, &status, WNOHANG);
		LOG.debug() << "Deleting task because of non-positive value of read" << std::endl;
		return on_close(fd);
	}
	_buffer->append(tmp, ret);
	// If the end of headers is not reached, parse the headers
	if (_state != S_BODY) {
		parse(response);
		// If the state changed after parsing, change the buffer reference to 
		// the one of the ActiveHTTP
		if (_state == S_BODY) {
			//if (_content_length == -1)
				//response.set_header("Transfer-Encoding", "chunked");
			_serv.write_beginning_on_write_buffer();
			_serv.get_write_buffer() += *_buffer;
			delete _buffer;
			_buffer = &_serv.get_write_buffer();
		}
	}
	return (true);
}

bool CGITask::on_writable(int) {
	return (true);
}

bool CGITask::always(int) {
	return (true);
}

bool	CGITask::on_close(int) { 
	delete (this);
	return (false);
}

bool CGITask::parse(Response &response) {
	bool keep_on_going = true;
	while (keep_on_going)
	{
		switch ((int)_state) {
			case S_HEADER_NAME:
				keep_on_going = parse_header_name();
				break;
			case S_HEADER_VALUE:
				keep_on_going = parse_header_value(response);
				break;
			default:
				break;
		}
	}
	*_buffer = _buffer->substr(_index);
	_index = 0;
	return true;
}

bool CGITask::parse_header_name() {
	size_t res;
	if ((res = _buffer->find("\r\n", _index)) != std::string::npos && res == 0)
	{
		_index = res + 2;
		_state = S_BODY;
		return false;
	}
	if ((res = _buffer->find(":", _index)) != std::string::npos)
	{
		_header_name = _buffer->substr(_index, res - _index);
		_index = res + 1;
		_state = S_HEADER_VALUE;
		return true;
	}
	return (false);
}

bool CGITask::parse_header_value(Response& response) {
	static int use = 0;
	use++;
	size_t res = _buffer->find("\r\n", _index);
	if (res != std::string::npos)
	{
		response.set_header(_header_name
							, _buffer->substr(_index, res - _index));
		if (_header_name == "Content-Length")
			_content_length =
				atoi(response.get_headers().at("Content-Length").c_str());
		_header_name = "";
		_index = res + 2;
		_state = S_HEADER_NAME;
		return (true);
	}
	return (false);
}
