#ifndef LOG_HPP
#define LOG_HPP
#include <iostream>
#include <ostream>
#include <sstream>
#include <iomanip>
#include <map>
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

private:
	log_level_t _level;
	NullStream _nullStream;
	std::map<log_level_t, std::string> _levels_to_str;
	std::map<char, std::string> _months_to_str;

public:
	Log();
	void setLevel(log_level_t level);

	std::ostream& log(log_level_t level);
	std::ostream& debug();
	std::ostream& info();
	std::ostream& warning();
	std::ostream& error();
};

#endif
