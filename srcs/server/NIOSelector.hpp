#ifndef NIOSELECTOR_HPP
#define NIOSELECTOR_HPP

#include <unistd.h>
#include <iostream>
#include <map>
#include <vector>
#include <poll.h>
#include "../utils/Singleton.hpp"
#include "../utils/Log.hpp"

#define READ	POLLIN
#define WRITE	POLLOUT

	/*class Callback {
	public:
		Callback() : _closed(false){}
		Callback(const Callback& src) : _closed(src._closed){}
		Callback& operator=(const Callback& src) {_closed = src._closed; return *this;}
		virtual ~Callback();
		virtual bool	on_writable(int fd) = 0;
		virtual bool	on_readable(int fd) = 0;
		virtual bool	on_close(int fd) = 0;
		virtual bool	always(int fd) = 0;
		bool getClosed() {return _closed;};
		void setClosed(bool closed) { _closed = closed;};

	protected:
		bool _closed;
	};*/

class NIOSelector : public Singleton<NIOSelector> {
	public:
	class Callback {
	public:
		Callback();
		Callback(const Callback&);
		Callback& operator=(const Callback&);
		virtual ~Callback();
		virtual bool	on_writable(int fd) = 0;
		virtual bool	on_readable(int fd) = 0;
		virtual bool	on_close(int fd) = 0;
		virtual bool	always(int fd) = 0;
	};

	typedef struct	s_action {
		unsigned long	index;
		Callback*		callback;
	}				t_action;

    private:
		std::map<int, t_action>		_actions;
		std::vector<struct pollfd>	_polled_fds;
		int							_timeout;
		NIOSelector(const NIOSelector&);
		NIOSelector& operator=(const NIOSelector&);

    public:
		static Log& LOG;

		NIOSelector();
        virtual ~NIOSelector();

		void	setTimeout(int timeout);
		void	add(int fd, Callback&, short operations=READ | WRITE);

		void	my_add(int fd, Callback&, short operations=READ | WRITE);

		void	updateOps(int fd, short operations=READ | WRITE);
		void	removeOps(int fd, short operations=READ | WRITE);
		void	remove(int fd);
		void	poll();
};

#endif
