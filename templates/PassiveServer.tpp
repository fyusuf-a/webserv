template<typename T>
PassiveServer<T>::PassiveServer() : Callback() {
	_socket = new Socket();
}

template<typename T>
PassiveServer<T>::PassiveServer(const PassiveServer& src) : Callback(src) {
	*this = src;
}

template<typename T>
PassiveServer<T>& PassiveServer<T>::operator=(const PassiveServer& src) {
	if (this != &src) {
		Callback::operator=(src);
		_socket = new Socket(*src._socket);
	}
	return *this;
}

template<typename T>
PassiveServer<T>::PassiveServer(short port, bool nonblocking) {
	_socket = new Socket(port, nonblocking);
	_socket->listen();
	NIOSelector::getInstance()->add(_socket->getFd(), *this, READ);
}

template<typename T>
PassiveServer<T>::~PassiveServer() {
	delete _socket;
}

template<typename T>
void			PassiveServer<T>::readable(int fd) {
	(void)fd;
#ifdef DEBUG
	std::cerr << "New connection on passive server" << std::endl;
#endif
	T* newActiveServer = new T(_socket->accept());
	NIOSelector::getInstance()->add(newActiveServer->getSocket()->getFd(), 
			*newActiveServer, READ | WRITE);
}

template<typename T>
void			PassiveServer<T>::writable(int fd) {
	(void)fd;
}

template<typename T>
void			PassiveServer<T>::on_close(int fd) {
	(void)fd;
}