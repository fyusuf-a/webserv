#ifndef LOG_HPP
#define LOG_HPP
#include <iostream>
#include <ostream>
#include <sstream>
#include <iomanip>
#include <map>
#include "../utils/Singleton.hpp"

class NullBuffer : public std::streambuf {
public:
	int overflow(int c) { return c; }
};

typedef enum {
	DEBUG,
	INFO,
	WARNING,
	ERROR,
	NONE
} log_level_t;

class Log : public Singleton<Log> {

private:
	log_level_t _level;
	NullBuffer _nullBuffer;
	std::ostream _nullStream;
	std::map<log_level_t, std::string> _levels_to_str;

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
