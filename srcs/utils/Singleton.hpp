#ifndef SINGLETON_HPP
#define SINGLETON_HPP
#include <iostream>

template <typename T>
class Singleton
{
public:
	static T& getInstance() {
		static T singleton;
		return (singleton);
	}
};

#endif
