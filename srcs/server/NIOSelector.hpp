#ifndef NIOSELECTOR_HPP
#define NIOSELECTOR_HPP

#include <unistd.h>
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>
#include <poll.h>
#include "../utils/Singleton.hpp"

#define READ	POLLIN
#define WRITE	POLLOUT

class NIOSelector : public Singleton<NIOSelector> {
	public:
	class Callback {
	public:
		Callback();
		Callback(const Callback&);
		Callback& operator=(const Callback&);
		virtual ~Callback();
		virtual void	on_writable(int fd) = 0;
		virtual void	on_readable(int fd) = 0;
		virtual void	on_close(int fd) = 0;
		virtual void	always(int fd) = 0;
	};

	typedef struct	s_action {
		unsigned long	index;
		Callback*		callback;
	}				t_action;

    private:
		std::map<int, t_action>		_actions;
		std::vector<struct pollfd>	_polled_fds;
		int							_timeout;
        NIOSelector(int timeout);
		NIOSelector(const NIOSelector&);
		NIOSelector& operator=(const NIOSelector&);

    public:
        virtual ~NIOSelector();

		static NIOSelector* getInstance(int timeout = 1000);
		void	add(int fd, Callback&, short operations=READ | WRITE);
		void	updateOps(int fd, short operations=READ | WRITE);
		void	removeOps(int fd, short operations=READ | WRITE);
		void	remove(int fd);
		void	poll();
};

#endif
