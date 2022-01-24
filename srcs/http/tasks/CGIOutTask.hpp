#ifndef CGIOUTTASK_HPP
#define CGIOUTTASK_HPP
#include "../../server/NIOSelector.hpp"
#include "../../utils/Log.hpp"
#include "../../utils/TransferEncoding.hpp"
#include "../../defines.hpp"
#include "../middlewares/MiddlewareChain.hpp"
#include "Task.hpp"

class CGIOutTask : public Task
{
    public:
		enum parsing_state {
			S_WAITING_FOR_MIDDLEWARES,
			S_HEADER_NAME,
			S_HEADER_VALUE,
			S_BODY
		};

        virtual ~CGIOutTask();
        CGIOutTask(int fd, ActiveHTTP &serv, int pid);


    protected:
        virtual bool on_readable(int);
        virtual bool on_writable(int);
        virtual bool on_close(int);
        virtual bool always(int);

		// Contains a temporary string buffer or is a direct pointer to the
		// write buffer of the ActiveHTTP server
		std::string		_buffer;
		std::string		_header_name;
		parsing_state	_state;
		size_t			_index;
		int				_pid;
		// This value is initialized to -1, if it non-negative at the end of the
		// parsing, a Content-Length header was encountered and this value
		// reflects it, otherwise, the response must be chunked
		ssize_t			_content_length;
		int				_status; // a temporary variable to check the exit value

	private:
		bool parse(Response&);
		bool parse_header_name();
		void parse_custom_status(Response& response, size_t res);
		bool parse_header_value(Response&);
};

#endif
