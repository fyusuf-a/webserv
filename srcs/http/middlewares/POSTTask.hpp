#ifndef POSTTASK_HPP
#define POSTTASK_HPP
#include "../../server/NIOSelector.hpp"
#include "../../utils/Log.hpp"
#include "../../defines.hpp"

#include "MiddlewareChain.hpp"

class POSTTask : public NIOSelector::Callback
{
    private: 
        ActiveHTTP	*_serv;
		ssize_t     _head;      

    public:
        POSTTask();
        ~POSTTask();
        POSTTask(const POSTTask&);
		POSTTask(int fd, ActiveHTTP *serv);

		static Log& LOG;


    protected:
    virtual bool   on_readable(int fd);
    virtual bool   on_writable(int);
    virtual bool   on_close(int);
    virtual bool   always(int);
};

#endif
