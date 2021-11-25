#ifndef GETTASK_HPP
#define GETTASK_HPP
#include "../../server/NIOSelector.hpp"
#include "../../utils/Log.hpp"

#include "MiddlewareChain.hpp"

class GETTask : public NIOSelector::Callback
{
    private: 
        MiddlewareChain  *_chain;
        ActiveHTTP       *_serv;

        Response         *_resp;

    public:
        GETTask();
        ~GETTask();
        GETTask(const GETTask&);
        GETTask(int fd, MiddlewareChain *chain, Response *resp, ActiveHTTP *serv);

		static Log& LOG;


    protected:
    virtual bool   on_readable(int fd);
    virtual bool   on_writable(int);
    virtual bool   on_close(int);
    virtual bool   always(int);
};

#endif
