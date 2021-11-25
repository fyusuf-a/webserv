#include "GETTask.hpp"

Log &GETTask::LOG = Log::getInstance();


GETTask::GETTask() : Callback() {
}

GETTask::GETTask(const GETTask& src) : Callback(src) {
	*this = src;
}

GETTask::GETTask(int fd, MiddlewareChain *chain) : _chain(chain) {
	NIOSelector::getInstance().add(fd, *this, READ);
}

GETTask::~GETTask(){}



bool GETTask::on_readable(int fd)
{
	int  ret;
	char buf[1000];
	std::string result;

	memset(buf, '\0', 10);



	if ((ret = read(fd, buf, 10)) == 0 )
		std::cout << "end of file" << std::endl;
	result = buf;
	std::cout << ret << std::endl;
	if (ret == 0)
	{
		on_close(fd);
		return (false);
	}

	std::cout << result << std::endl;
	(void)_chain;
	(void)fd;
	(void)ret;
	return (true);

}
bool    GETTask::on_writable(int) { return (true); };
bool	GETTask::on_close(int fd) { 
    NIOSelector::getInstance().remove(fd);
	delete (this);
	return (false);
}
bool    GETTask::always(int) { return (true); };
