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
		enum parsing_state {
			S_HEADER_NAME,
			S_HEADER_VALUE,
			S_BODY
		};

        ~CGITask();
        CGITask(int fd, ActiveHTTP &serv, int pid);


    protected:
        virtual bool   on_readable(int fd);
        virtual bool   on_writable(int);
        virtual bool   on_close(int);
        virtual bool   always(int);

		// Contains a temporary string buffer or is a direct pointer to the
		// write buffer of the ActiveHTTP server
		std::string*	_buffer;
		std::string		_header_name;
		parsing_state	_state;
		size_t			_index;
		int				_pid;

	private:
		bool parse(Response&);
		bool parse_header_name();
		bool parse_header_value(Response&);
};

#endif
