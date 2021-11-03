#ifndef SINGLETON_HPP
#define SINGLETON_HPP
#include <iostream>

template <typename T>
class Singleton
{
protected:
	static T* _singleton;

public:
	static T& getInstance() {
		if (_singleton == NULL)
			_singleton = new T();
		return *_singleton;
	}
	static void destroyInstance() {
		delete _singleton;
	}
};

template <typename T>
T* Singleton<T>::_singleton = NULL;

#endif
