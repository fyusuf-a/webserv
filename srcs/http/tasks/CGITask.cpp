#include "CGITask.hpp"

// Log &CGITask::LOG = Log::getInstance();

CGITask::CGITask() : Task() {
}

CGITask::CGITask(const CGITask& src) : Task(src) {
	*this = src;
}

CGITask::CGITask(int fd, ActiveHTTP *serv) : Task(fd, serv, READ) {
}

CGITask::~CGITask(){}

bool CGITask::on_readable(int fd) {
// 	int  ret;
// 	char buf[1000];
// 	std::string result;

// 	memset(buf, '\0', 10);

// 	if ((ret = read(fd, buf, 10)) == 0 )
// 		std::cout << "end of file" << std::endl;
// 	result = buf;
// 	std::cout << ret << std::endl;
// 	if (ret == 0)
// 	{
// 		on_close(fd);
// 		return (false);
// 	}

// 	std::cout << result << std::endl;
// 	(void)_chain;
// 	(void)fd;
// 	(void)ret;
// 	return (true);
	return (true);
}

bool    CGITask::on_writable(int) {
	return (true);
};

bool	CGITask::always(int fd) {
	return (true);
}

bool	CGITask::on_close(int) { 
	delete (this);
	return (false);
}
