#include "CGITask.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


CGITask::CGITask(int fd, ActiveHTTP& serv, int pid)
		: Task(fd, serv, READ)
		, _state(S_HEADER_NAME)
		, _index(0)
		, _pid(pid)
		, _content_length(-1)
{
}

CGITask::~CGITask(){
	waitpid(_pid, NULL, WNOHANG);
	TransferEncoding::final_chunk_on_buffer(_serv.get_write_buffer());
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

	// If no data is read from the pipe, delete the task
	if (ret <= 0)
	{
		LOG.debug() << "Deleting task because of non-positive value of read" << std::endl;
		return on_close(fd);
	}
	// If the end of headers is not reached, parse the headers
	if (_state != S_BODY)
	{
		_buffer.append(tmp, ret);
		parse(response);
		// If the state changed after parsing, change the buffer reference to 
		// the one of the ActiveHTTP
		_buffer = _buffer.substr(_index);
		_index = 0;
		if (_state == S_BODY)
		{
			if (_content_length == -1)
			{
				response.delete_header("Content-Length");
				response.set_header("Transfer-Encoding", "chunked");
			}
			_serv.write_beginning_on_write_buffer();
			if (_content_length == -1)
				TransferEncoding::to_chunk_on_buffer(_serv.get_write_buffer(),
																	_buffer);
			else
				_serv.get_write_buffer() += _buffer;
		}
	}
	else if (_state == S_BODY) {
		if (_content_length == -1)
			TransferEncoding::to_chunk_on_buffer(_serv.get_write_buffer(),
																	tmp, ret);
		else
			_serv.get_write_buffer().append(tmp, ret);
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
	//_buffer = _buffer.substr(_index);
	//_index = 0;
	return true;
}

bool CGITask::parse_header_name() {
	size_t res;
	if ((res = _buffer.find("\r\n", _index)) != std::string::npos && res == _index)
	{
		_index = res + 2;
		_state = S_BODY;
		return false;
	}
	if ((res = _buffer.find(":", _index)) != std::string::npos)
	{
		_header_name = _buffer.substr(_index, res - _index);
		_index = res + 1;
		_state = S_HEADER_VALUE;
		return true;
	}
	return (false);
}

bool CGITask::parse_header_value(Response& response) {
	static int use = 0;
	use++;
	size_t res = _buffer.find("\r\n", _index);
	if (res != std::string::npos)
	{
		response.set_header(_header_name
							, _buffer.substr(_index, res - _index));
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
