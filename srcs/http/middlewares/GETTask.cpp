#include "GETTask.hpp"

GETTask::GETTask(int fd, MiddlewareChain *) {
	NIOSelector::getInstance().add(fd, *this, READ);
}
GETTask::~GETTask(){}


bool GETTask::on_readable(int)
{
    (void)_chain;
    return (false);

}
bool    GETTask::on_writable(int) { return (true); };
bool	GETTask::on_close(int) { return (true); }
bool    GETTask::always(int) { return (true); };
