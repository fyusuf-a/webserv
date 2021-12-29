#ifndef POSTTASK_HPP
#define POSTTASK_HPP
#include "../../server/NIOSelector.hpp"
#include "../../utils/Log.hpp"
#include "../../defines.hpp"

#include "../middlewares/MiddlewareChain.hpp"
#include "Task.hpp"

#define POST_BUFFER_LENGTH 10000000

class POSTTask : public Task
{
    private: 
		enum state {
			S_WAITING_FOR_MIDDLEWARES,
			S_BEGINNING_WRITTEN
		};

		ssize_t     _head;      
		size_t		_size;

    public:
		enum does_write_on_write_buffer {
			WRITE_ON_WRITE_BUFFER,
			NO_WRITE_ON_WRITE_BUFFER,
		};

        virtual ~POSTTask();
		POSTTask(int fd, ActiveHTTP& serv, does_write_on_write_buffer condition = WRITE_ON_WRITE_BUFFER);

    protected:
        virtual bool	on_readable(int fd);
        virtual bool	on_writable(int);
        virtual bool	on_close(int);
        virtual bool	always(int);
		state			_state;
		does_write_on_write_buffer
						_output_to_write_buffer;
};

#endif
