#include "../../includes/ActiveSocket.hpp"
#include "../../includes/INetAddress.hpp"

ActiveSocket::ActiveSocket() : Socket() {
}

ActiveSocket::ActiveSocket(const ActiveSocket& src) : Socket(src), NIOSelector::Callback(src) {
	*this = src;
}

ActiveSocket& ActiveSocket::operator=(const ActiveSocket& src) {
	Socket::operator=(src);
	return *this;
}

ActiveSocket::ActiveSocket(short port, bool nonblocking) {
	Socket(port, nonblocking);
}

ActiveSocket::~ActiveSocket() {
#ifdef DEBUG
	std::cerr << "Connection closed with " << _address << std::endl;
#endif
}

ssize_t ActiveSocket::send(const std::string& message, int flags)
{
	return ::send(_fd, message.c_str(), message.length(), flags);
}

ssize_t ActiveSocket::send(const void *msg, ssize_t len, int flags)
{
	ssize_t ret = ::send(_fd, msg, len, flags);
	if (ret < 0)
		std::cerr << "send: error" << std::endl;
	return ret;
}

/*std::string ActiveSocket::recv(ssize_t maxlen, int flags)
{
	char	tmp[maxlen];
	ssize_t ret = recv(tmp, maxlen, flags);
	return (std::string(tmp, ret));
}*/

ssize_t ActiveSocket::recv(void *buf, ssize_t maxlen, int flags)
{
	ssize_t ret = ::recv(_fd, buf, maxlen, flags);
	if (ret < 0)
		std::cerr << "recv: error" << std::endl;
	if (ret <= 0)
		on_close(_fd);
	return (ret);
}

void ActiveSocket::readable(int fd) {
	(void)fd;
	ssize_t max_read = BUFFER_LENGTH - _read_buffer.length();
	char tmp[max_read];
	if (max_read > 0)
		_read_buffer += recv(tmp, max_read);
}

void ActiveSocket::writable(int fd) {
	(void)fd;
	size_t len = std::min<size_t>(BUFFER_LENGTH, _write_buffer.length());

	if (len > 0)
	{
		send(_write_buffer.substr(0, len), len);
		_read_buffer = _write_buffer.substr(len);
	}
}

void ActiveSocket::on_close(int fd) {
	NIOSelector::getInstance()->remove(fd);
	delete (this);
}
