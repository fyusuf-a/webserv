#include "CGIOutTask.hpp"
#include <cstdlib>
#include <stdexcept>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cctype>


CGIOutTask::CGIOutTask(int fd, ActiveHTTP& serv, int pid)
		: Task(fd, serv, READ)
		, _state(S_HEADER_NAME)
		, _index(0)
		, _pid(pid)
		, _content_length(-1)
{
	LOG.debug() << "New CGIOut task (fd = " << _fd << ")" << std::endl;
}

CGIOutTask::~CGIOutTask() {
	int status;
	waitpid(_pid, &status, WNOHANG);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		Response& response = _serv.get_response();
		response.set_code(Response::InternalServerError);
		response.set_header("Content-Length", 0, true);
		response.delete_header("Transfer-Encoding");
		_serv.write_beginning_on_write_buffer(_fd);
	}
	TransferEncoding::final_chunk_on_buffer(_serv.get_write_buffer());
}

bool CGIOutTask::on_readable(int fd) {
	Response& response = _serv.get_response();

	// Read from the pipe
	char* tmp = _serv.get_tmp();
	ssize_t ret = read(fd, tmp, BUFFER_LENGTH);

	// If no data is read from the pipe, delete the task
	if (ret <= 0)
	{
		waitpid(_pid, &_status, WNOHANG);
		if (WIFEXITED(_status)) {
			LOG.debug() << "Process has exited  and read returned a "
				"non-positive value (fd = " << fd << ")" << std::endl;
			on_close(fd);
			return false;
		}
		return true;
	}

	bool is_head_method = _serv.get_request().get_method() == "HEAD";
	// If the end of headers is not reached, parse the headers
	if (_state != S_BODY)
	{
		_buffer.append(tmp, ret);
		parse(response);
		// If the state changed after parsing, change the buffer reference to 
		// the one of the ActiveHTTP
		if (_state == S_BODY)
		{
			if (_content_length == -1)
			{
				response.delete_header("Content-Length");
				response.set_header("Transfer-Encoding", "chunked", true);
			}
			_serv.write_beginning_on_write_buffer(fd);
			if (!is_head_method && _content_length == -1)
				TransferEncoding::to_chunk_on_buffer(
										_serv.get_write_buffer(), _buffer);
			else if (!is_head_method)
				_serv.get_write_buffer() += _buffer;
		}
	}
	else if (_state == S_BODY) {
		if (!is_head_method && _content_length == -1)
			TransferEncoding::to_chunk_on_buffer(_serv.get_write_buffer(),
																	tmp, ret);
		else if (!is_head_method)
			_serv.get_write_buffer().append(tmp, ret);
	}
	return (true);
}

bool CGIOutTask::on_writable(int) {
	return (true);
}

bool CGIOutTask::always(int) {
	return (true);
}

bool CGIOutTask::on_close(int fd) { 
	static bool first_call = true;
	if (first_call)
	{
		first_call = false;
		on_readable(fd);
		return (false);
	}
	first_call = true;
	delete (this);
	return (false);
}

bool CGIOutTask::parse(Response &response) {
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
	_buffer = _buffer.substr(_index);
	_index = 0;
	return true;
}

bool CGIOutTask::parse_header_name() {
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

void CGIOutTask::parse_custom_status(Response& response, size_t res) {
	std::stringstream oss;
	oss << _buffer.substr(_index, res - _index);
	unsigned int response_code;
	oss >> response_code;
	response.set_code(response_code);

	char c;
	do {
		oss >> c;
	} while (c == ' ' || c == '\t');
	std::string reason_phrase;
	getline(oss, reason_phrase);
	response.set_custom_reason_phrase(c + reason_phrase);
}

bool CGIOutTask::parse_header_value(Response& response) {
	size_t res = _buffer.find("\r\n", _index);
	if (res != std::string::npos)
	{
		// Lose leading space
		char c;
		while (_index < res)
		{	
			if ((c = _buffer[_index]) == ' ' || c == '\t')
				_index++;
			else
				break;
		}
		// Supersede the value given by Webserv to the response
		if (Utils::cmpStringInsensitive::is_equal(_header_name, "Content-Type")) {
			response.set_header(_header_name
				, _buffer.substr(_index, res - _index), true);
		}
		else if (Utils::cmpStringInsensitive::is_equal(_header_name, "Content-Length")) {
			try {
				std::string content_length_str =
					HeaderMap::get_header_first_value(response.get_headers(), "Content-Length");
				_content_length = atoi(content_length_str.c_str());
			}
			catch (std::out_of_range& e) {
			}
		}
		else {
			if (Utils::cmpStringInsensitive::is_equal(_header_name, "Status"))
				parse_custom_status(response, res);
			response.set_header(_header_name
				, _buffer.substr(_index, res - _index), false);
		}
		_header_name = "";
		_index = res + 2;
		_state = S_HEADER_NAME;
		return (true);
	}
	return (false);
}
