#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <sstream>
#include <iomanip>

typedef enum {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
} log_level_t;

extern log_level_t g_log_level;

template<std::ostream& os = std::cout>
class Log {
public:
    Log(log_level_t level = INFO) : _level(level) {
		time_t rawtime;
		struct tm* t;
		time(&rawtime);
		t = localtime(&rawtime);
        if (g_log_level <= _level) {
            /*switch (_level) {
                case DEBUG:
                    _buffer << "[debug]: ";
                break;
                case INFO:
                    _buffer << "[info]: ";
                break;
                case WARNING:
                    _buffer << "[warning]: ";
                break;
                case ERROR:
                    _buffer << "[error]: ";
                break;
                default:
                break;
            }*/
			_buffer << "[" << 1900 + t->tm_year << "/";
			switch (t->tm_mon) {
				case 0: _buffer << "Jan"; break;
				case 1: _buffer << "Feb"; break;
				case 2: _buffer << "Mar"; break;
				case 3: _buffer << "Apr"; break;
				case 4: _buffer << "May"; break;
				case 5: _buffer << "Jun"; break;
				case 6: _buffer << "Jul"; break;
				case 7: _buffer << "Aug"; break;
				case 8: _buffer << "Sep"; break;
				case 9: _buffer << "Oct"; break;
				case 10: _buffer << "Nov"; break;
				case 11: _buffer << "Dec"; break;
				default: break;
			}
			_buffer << "/" << std::setfill('0') << std::setw(2) << t->tm_mday
					<< ":" << std::setfill('0') << std::setw(2) << t->tm_hour
					<< ":" << std::setfill('0') << std::setw(2) << t->tm_min
					<< ":" << std::setfill('0') << std::setw(2) << t->tm_sec << "] ";
        }
    }
    ~Log() {
        if (g_log_level <= _level) {
            os << _buffer.str() << std::endl;
        }
    }

    template<typename T>
    Log& operator<<(T const& value) {
        if (g_log_level <= _level) {
            _buffer << value;
        }
        return *this;
    }

private:
    std::ostringstream _buffer;
    log_level_t _level;
};

/*#include <iostream>
#include <ostream>
#include <sstream>
#include "../utils/Singleton.hpp"

class NullStream : public std::ostream {
	NullStream() : std::ostream() {
	}
	virtual ~NullStream() {
	}
};

template<typename T>
void operator<<(const NullStream& os, const T&) {
	(void)os;
}

enum log_level_t {
	DEBUG,
	INFO,
	WARNING,
	ERROR,
};

extern log_level_t g_log_level;

template<std::ostream& os = std::cout>
class Log : Singleton<Log<os> > {
public:
	static Log* getInstance(log_level_t level) {
		if (_singleton == NULL)
			_singleton = new Log(level);
		return _singleton;
	}
private:
	Log(log_level_t level) {
		(void)level;
		_debug = level < DEBUG ? nullStream : os;
		_info = level < INFO ? nullStream : os;
		_warning = level < WARNING ? nullStream : os;
		_error = level < ERROR ? nullStream : os;
		debug = level < DEBUG ? nullStream : os;
		info = level < INFO ? nullStream : os;
		warning = level < WARNING ? nullStream : os;
		error = level < ERROR ? nullStream : os;
	}
	static NullStream nullStream;
	static std::ostream& _debug;
	static std::ostream& _info;
	static std::ostream& _warning;
	static std::ostream& _error;

	public:
	static void setLogLevel(log_level_t level) {
		debug = level < DEBUG ? nullStream : os;
		info = level < INFO ? nullStream : os;
		warning = level < WARNING ? nullStream : os;
		error = level < ERROR ? nullStream : os;
		(void)level;
		debug = os;
		info = os;
		warning = os;
		error = os;
	}

};*/

/*template<std::ostream& os = std::cout>
class Log {
	public:
	Log(log_level_t level = INFO) {
		if (g_log_level < level)
			_buffer = NullStream();
		switch (level) {
			case DEBUG:
				_buffer << "[debug]: ";
			break;
			case INFO:
				_buffer << "[info]: ";
			break;
			case WARNING:
				_buffer << "[warning]: ";
			break;
			case ERROR:
				_buffer << "[error]: ";
			break;
			default:
			break;
		}
	}
	~Log() {
		_buffer << std::endl;
		os << _buffer.str();
	}

	template<typename T>
	Log& operator<<(T const& value) {
		_buffer << value;
		return *this;
	}

	private:
	std::ostringstream _buffer;
};*/

#endif
