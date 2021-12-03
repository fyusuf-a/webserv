#ifndef GETTASK_HPP
#define GETTASK_HPP
#include "../../server/NIOSelector.hpp"
#include "../../utils/Log.hpp"
#include "../../defines.hpp"
#include "../middlewares/MiddlewareChain.hpp"
#include "Task.hpp"

class GETTask : public Task
{
    private: 
        //ActiveHTTP		*_serv;
		bool			_finished;
		ssize_t			_file_size;

    public:
        GETTask();
        ~GETTask();
        GETTask(const GETTask&);
        //GETTask(int fd, ActiveHTTP *serv);
		GETTask(int fd, ActiveHTTP *serv, ssize_t file_size);

		static Log& LOG;


    protected:
    virtual bool   on_readable(int fd);
    virtual bool   on_writable(int);
    virtual bool   on_close(int);
    virtual bool   always(int);
};

#endif
