#include "../../includes/NIOSelector.hpp"
#include <poll.h>
#include <stdexcept>

NIOSelector::Callback::Callback() {
}

NIOSelector::Callback::Callback(const Callback& src) {
	*this = src;
}

NIOSelector::Callback& NIOSelector::Callback::operator=(const Callback&) {
	return *this;
}

NIOSelector::Callback::~Callback() {}

NIOSelector::NIOSelector(int timeout) : _timeout(timeout) {
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

void	NIOSelector::add(int fd, Callback& callback, short operations) {
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
		std::cerr << "fd " << fd << " does not exist in map." << std::endl;
}

void	NIOSelector::removeOps(int fd, short operations) {
	if (_actions.find(fd) != _actions.end())
		_polled_fds[_actions[fd].index].events &= ~operations;
	else
		std::cerr << "fd " << fd << " does not exist in map." << std::endl;
}

void	NIOSelector::remove(int fd) {
	if (_actions.find(fd) != _actions.end())
		_polled_fds.erase(_polled_fds.begin() + _actions[fd].index);
	else
		std::cerr << "fd " << fd << " does not exist in map." << std::endl;
}

void	NIOSelector::poll() throw (std::runtime_error) {
	int ret = ::poll(_polled_fds.data(), _polled_fds.size(), _timeout);
	int fd;

	if (ret < 0)
		throw std::runtime_error("poll: unexpected error");
	for (unsigned long i = 0; i < _polled_fds.size(); i++) {
		fd = _polled_fds[i].fd;
		if (_polled_fds[i].revents & (POLLIN | POLLPRI))
			_actions[fd].callback->readable(fd);
		if (_polled_fds[i].revents & POLLOUT)
			_actions[fd].callback->writable(fd);
		if (_polled_fds[i].revents & (POLLERR | POLLNVAL))
		{
			std::cerr << "An error has occured" << std::endl;
			_actions[fd].callback->on_close(fd);
			remove(fd);
		}
		else if (_polled_fds[i].revents & (POLLHUP | POLLRDHUP))
		{
			std::cerr << "Peer closed the connection" << std::endl;
			_actions[fd].callback->on_close(fd);
			remove(fd);
		}
	}
}
