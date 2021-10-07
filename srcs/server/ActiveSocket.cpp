#include "../../includes/ActiveSocket.hpp"
#include "../../includes/INetAddress.hpp"

ActiveSocket::ActiveSocket() : Socket() {
}

ActiveSocket::ActiveSocket(const ActiveSocket& src) : Socket(src) {
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
}

ssize_t ActiveSocket::send(const std::string& message, int flags) throw (std::runtime_error)
{
	return ::send(_fd, message.c_str(), message.length(), flags);
}

ssize_t ActiveSocket::send(const void *msg, int len, int flags) throw (std::runtime_error)
{
	ssize_t ret = ::send(_fd, msg, len, flags);
	if (ret < 0)
		throw std::runtime_error("send: error");
	return ret;
}

std::string ActiveSocket::recv(int maxlen, int flags) throw (std::runtime_error)
{
	char	tmp[maxlen];
	ssize_t ret = recv(tmp, maxlen, flags);
	return (std::string(tmp, ret));
}

ssize_t ActiveSocket::recv(void *buf, int maxlen, int flags) throw (std::runtime_error)
{
	ssize_t ret = ::recv(_fd, buf, maxlen, flags);
	if (ret < 0)
		throw std::runtime_error("recv: error");
	if (ret == 0)
		throw std::runtime_error("recv: remote host closed connection");
	return (ret);
}
