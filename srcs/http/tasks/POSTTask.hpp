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
		enum state {
			S_WAITING_FOR_MIDDLEWARES,
			S_BEGINNING_WRITTEN
		};

		ssize_t     _head;      

    public:
        ~POSTTask();
		POSTTask(int fd, ActiveHTTP& serv);

    protected:
        virtual bool	on_readable(int fd);
        virtual bool	on_writable(int);
        virtual bool	on_close(int);
        virtual bool	always(int);
		state			_state;
};

#endif
