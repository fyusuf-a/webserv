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

	std::cout << "CGITask: on_readable" << std::endl;
	if (!response.get_ready())
		return true;

	// Read from the pipe
	char* tmp = _serv.get_tmp();
	ssize_t ret = read(fd, tmp, BUFFER_LENGTH);

	int status;
	// If no data is read from the pipe, do not do anything or delete the task
	if (ret <= 0)
	{
		int pid = waitpid(_pid, &status, WNOHANG);
		if (pid == _pid && WIFEXITED(status))
		{
			on_close(fd);
			return false;
		}
		return true;
	}
	_buffer->append(tmp, ret);
	// If the end of headers is not reached, parse the headers
	if (_state != S_BODY) {
		parse(response);
		// If the state changed after parsing, change the buffer reference to 
		// the one of the ActiveHTTP
		if (_state == S_BODY) {
			std::cout << "CGITask: changing state" << std::endl;
			std::string temp = *_buffer;
			_serv.write_beginning_on_write_buffer();
			response.set_beginning_written_on_write_buffer(true);
			delete _buffer;
			_buffer = &_serv.get_write_buffer();
			*_buffer += temp;
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
	size_t res = _buffer->find(":", _index);
	if (res != std::string::npos)
	{
		_header_name = _buffer->substr(_index, res - _index);
		_index = res + 1;
		_state = S_HEADER_VALUE;
		return true;
	}
	if ((res = _buffer->find("\r\n", _index)) != std::string::npos)
	{
		_index = res + 2;
		_state = S_BODY;
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
		_header_name = "";
		_index = res + 2;
		_state = S_HEADER_NAME;
		return (true);
	}
	return (false);
}
