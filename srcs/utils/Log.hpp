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
	
	void setLevel(log_level_t level);

	std::ostream& debug();
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
		std::ostream& os = level < _level ? _nullStream : std::cout;
		if (level < _level)
			return _nullStream;
		time_t rawtime;
		struct tm* t;
		time(&rawtime);
		t = localtime(&rawtime);
		os << "[" << 1900 + t->tm_year << "/";
		os << std::setfill('0') << std::setw(2) << _months_to_str[t->tm_mon];
		os << "/" << std::setfill('0') << std::setw(2) << t->tm_mday
				<< ":" << std::setfill('0') << std::setw(2) << t->tm_hour
				<< ":" << std::setfill('0') << std::setw(2) << t->tm_min
				<< ":" << std::setfill('0') << std::setw(2) << t->tm_sec;
		os << " " << _levels_to_str[_level] << "] ";
		return os;
	}
	Log(log_level_t level) : _level(level) {
		_levels_to_str[DEBUG] = "debug";
		_levels_to_str[INFO] = "info";
		_levels_to_str[WARNING] = "warning";
		_levels_to_str[ERROR] = "error";
		_months_to_str[0] = "Jan";
		_months_to_str[1] = "Feb";
		_months_to_str[2] = "Mar";
		_months_to_str[3] = "Apr";
		_months_to_str[4] = "May";
		_months_to_str[5] = "Jun";
		_months_to_str[6] = "Jul";
		_months_to_str[7] = "Aug";
		_months_to_str[8] = "Sep";
		_months_to_str[9] = "Oct";
		_months_to_str[10] = "Nov";
		_months_to_str[11] = "Dec";
	}
};

#endif
