#include "../server/NIOSelector.hpp"
#include <poll.h>
#include <stdexcept>

Log &NIOSelector::LOG = Log::getInstance();

NIOSelector::Callback::Callback() {
}

NIOSelector::Callback::Callback(const Callback& src) {
	*this = src;
}

NIOSelector::Callback& NIOSelector::Callback::operator=(const Callback&) {
	return *this;
}

NIOSelector::Callback::~Callback() {}

NIOSelector::NIOSelector() : _timeout(0) {
}

NIOSelector::NIOSelector(const NIOSelector& src) {
	*this = src;
}

NIOSelector& NIOSelector::operator=(const NIOSelector& src) {
	if (this != &src) {
		_actions = src._actions;
		_polled_fds = src._polled_fds;
	}
	return (*this);
}

NIOSelector::~NIOSelector() {
}

void NIOSelector::setTimeout(int timeout) {
	_timeout = timeout;
}

void	NIOSelector::add(int fd, Callback& callback, short operations) {
	LOG.debug() << "Adding fd no " << fd << " to NIOSelector with operations "
		<< (operations & READ ? "READ/" : "") << (operations & WRITE ? "WRITE/" : "")  << std::endl;
	_actions[fd] = (t_action){_polled_fds.size(), &callback};
	_polled_fds.push_back((struct pollfd)
						{ fd
						  , operations
						  , 0});
}

void	NIOSelector::updateOps(int fd, short operations) {
	if (_actions.find(fd) != _actions.end())
		_polled_fds[_actions[fd].index].events = operations;
	else
		LOG.warning() << "fd " << fd << " does not exist in map. (updateOps)" << std::endl;
}

void	NIOSelector::removeOps(int fd, short operations) {
	if (_actions.find(fd) != _actions.end())
		_polled_fds[_actions[fd].index].events &= ~operations;
	else
		LOG.warning() << "fd " << fd << " does not exist in map. (removeOps)" << std::endl;
}

void	NIOSelector::remove(int fd) {
	std::map<int, t_action>::const_iterator match = _actions.find(fd);
	if (match != _actions.end())
	{
		_polled_fds.erase(_polled_fds.begin() + _actions[fd].index);
		for (std::map<int, t_action>::iterator it = _actions.begin(); it != _actions.end(); it++)
		{
			if (it->second.index >= _actions[fd].index)
				it->second.index--;
		}
	}
	else
		LOG.warning() << "fd " << fd << " does not exist in map. (remove)" << std::endl;
	_actions.erase(fd);
}

void	NIOSelector::poll() {
	int			ret = ::poll(_polled_fds.data(), _polled_fds.size(), _timeout);
	int			fd;
	time_t		now;
	short		revents;
	t_action	action;

	time(&now);
	if (ret < 0)
		throw std::runtime_error("poll: unexpected error");
	for (unsigned long i = 0; i < _polled_fds.size(); i++) {
		fd = _polled_fds[i].fd;
		revents = _polled_fds[i].revents;
		action = _actions[fd];
		action.callback->always(fd);
		if (revents & (POLLERR | POLLNVAL)) {
			LOG.error() << "An error has occured in the connection with peer" << std::endl;
			action.callback->on_close(fd);
			continue;
		}
		if (revents & POLLHUP) {
			LOG.info() << "Peer closed the connection" << std::endl << std::endl;
			action.callback->on_close(fd);
			continue;
		}
		if (revents & (POLLIN | POLLPRI) && !action.callback->on_readable(fd))
			continue;
		if (revents & POLLOUT && !action.callback->on_writable(fd))
			continue;
	}
}
