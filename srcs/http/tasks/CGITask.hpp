#ifndef CGITASK_HPP
#define CGITASK_HPP
#include "../../server/NIOSelector.hpp"
#include "../../utils/Log.hpp"
#include "../../defines.hpp"
#include "../middlewares/MiddlewareChain.hpp"
#include "Task.hpp"

class CGITask : public Task
{
    public:
        CGITask();
        ~CGITask();
        CGITask(const CGITask&);
        CGITask(int fd, ActiveHTTP *serv);

    protected:
        virtual bool   on_readable(int fd);
        virtual bool   on_writable(int);
        virtual bool   on_close(int);
        virtual bool   always(int);
};

#endif
