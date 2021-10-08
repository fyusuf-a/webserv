#ifndef NIOSELECTOR_HPP
#define NIOSELECTOR_HPP

#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>
#include <poll.h>
#include "utils/Singleton.hpp"

#define WRITE	POLLIN
#define READ	POLLOUT
#define CLOSE	POLLUP

class NIOSelector : public Singleton<NIOSelector> {
	public:
	class Callback {
	public:
		Callback();
		Callback(const Callback&);
		Callback& operator=(const Callback&);
		virtual ~Callback();
		virtual void	writable(int fd) = 0;
		virtual void	readable(int fd) = 0;
		virtual void	on_close(int fd) = 0;
	};

	typedef struct	s_action {
		unsigned long	index;
		Callback*		callback;
	}				t_action;

    private:
		std::map<int, t_action>		_actions;
		std::vector<struct pollfd>	_polled_fds;
		int							_timeout;

    public:
        NIOSelector(int timeout = 1000);
		NIOSelector(const NIOSelector&);
		NIOSelector& operator=(const NIOSelector&);
        virtual ~NIOSelector();

		void	add(int fd, Callback&, short operations=READ | WRITE);
		void	updateOps(int fd, short operations=READ | WRITE);
		void	removeOps(int fd, short operations=READ | WRITE);
		void	remove(int fd);
		void	poll() throw (std::runtime_error);
};

#endif

