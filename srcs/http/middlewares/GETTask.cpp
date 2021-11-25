#include "GETTask.hpp"

Log &GETTask::LOG = Log::getInstance();


GETTask::GETTask() : Callback() {
}

GETTask::GETTask(const GETTask& src) : Callback(src) {
	*this = src;
}

GETTask::GETTask(int fd, MiddlewareChain *chain, Response *resp, ActiveHTTP *serv) : _chain(chain), _serv(serv), _resp(resp) {
	NIOSelector::getInstance().add(fd, *this, READ);
}

GETTask::~GETTask(){}



bool GETTask::on_readable(int fd)
{
	int  ret;
	char hex[5];
	char buf[1000];
	std::string sep = "\r\n";
	std::string result;

	memset(buf, '\0', 10);

	ret = read(fd, buf, 5);
	if (ret == 0)
	{
		result += "0" + sep + sep;
		_resp->set_body(result);

		on_close(fd);

		(*_chain)();
		return (false);
	}
	sprintf(hex, "%X", ret);
	result += hex + sep + buf + sep;
	_resp->set_body(result);



	(void)_chain;
	(void)_serv;
	return (true);

}
bool    GETTask::on_writable(int) { return (true); };
bool	GETTask::on_close(int fd) { 
    NIOSelector::getInstance().remove(fd);
	delete (this);
	return (false);
}
bool    GETTask::always(int) { return (true); };
