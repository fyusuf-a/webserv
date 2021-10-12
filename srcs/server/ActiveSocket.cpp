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

