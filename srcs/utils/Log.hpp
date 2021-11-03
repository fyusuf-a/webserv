#ifndef LOG_HPP
#define LOG_HPP
#include <iostream>
#include <ostream>
#include <sstream>
#include "../utils/Singleton.hpp"

class NullStream : public std::ostream, Singleton<NullStream> {
	public:
	NullStream() : std::ostream() {
	}
	virtual ~NullStream() {
	}
};

template<typename T>
NullStream& operator<<(NullStream& os, const T&) {
	return os;
}

typedef enum {
	DEBUG,
	INFO,
	WARNING,
	ERROR,
} log_level_t;

class Log : public Singleton<Log> {
public:
	std::ostream& debug() {
		return log(DEBUG);
	}
	std::ostream& info() {
		return log(INFO);
	}
	std::ostream& warning() {
		return log(WARNING);
	}
	std::ostream& error() {
		return log(ERROR);
	}
	std::ostream& log(log_level_t level) {
		if (level < _level)
			return _nullStream;
		return std::cout;
	}
	static Log& getInstance(log_level_t level = ERROR) {
		if (_singleton == NULL)
			_singleton = new Log(level);
		return *_singleton;
	}
	Log(log_level_t level) : _level(level) {
	}
private:
	log_level_t _level;
	NullStream _nullStream;
};

#endif
