#ifndef POSTTASK_HPP
#define POSTTASK_HPP
#include "../../server/NIOSelector.hpp"
#include "../../utils/Log.hpp"
#include "../../defines.hpp"

#include "../middlewares/MiddlewareChain.hpp"
#include "Task.hpp"


class POSTTask : public Task
{
    private: 
		ssize_t     _head;      

    public:
        POSTTask();
        ~POSTTask();
        POSTTask(const POSTTask&);
		POSTTask(int fd, ActiveHTTP *serv);


    protected:
        virtual bool   on_readable(int fd);
        virtual bool   on_writable(int);
        virtual bool   on_close(int);
        virtual bool   always(int);
};

#endif
