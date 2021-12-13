#ifndef TASK_HPP
#define TASK_HPP
#include "../../server/ActiveHTTP.hpp"
#include "../../utils/utils.hpp"
#include "../../server/NIOSelector.hpp"

class Task : public NIOSelector::Callback { 
	protected:
		int			_fd;
		ActiveHTTP& _serv;

    public:
		static Log& LOG;
        Task(int fd, ActiveHTTP&, short mode);
        virtual ~Task();
};

#endif

