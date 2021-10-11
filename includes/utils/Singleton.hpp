#include <iostream>

template <typename T>
class Singleton
{
protected:
	static T* _singleton;

public:
	static T* getInstance() {
		if (_singleton == NULL)
			_singleton = new T();
		return _singleton;
	}
};

template <typename T>
T* Singleton<T>::_singleton = NULL;
