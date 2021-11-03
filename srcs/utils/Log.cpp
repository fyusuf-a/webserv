#include "Log.hpp"

void Log::setLevel(log_level_t level) {
	_level = level;
}

std::ostream& Log::log(log_level_t level) {
	std::ostream& os = level < _level ? _nullStream : std::cout;
	if (level < _level)
		return _nullStream;
	time_t rawtime;
	struct tm* t;
	time(&rawtime);
	t = localtime(&rawtime);
	os << "[" << 1900 + t->tm_year << "/";
	os << std::setfill('0') << std::setw(2) << _months_to_str[t->tm_mon];
	os << "/" << t->tm_mday
		<< ":" << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec
		<< " " <<  std::setfill(' ') << std::setw(7) << _levels_to_str[level] << "] ";
	return os;
}

std::ostream& Log::debug() {
	return log(DEBUG);
}

std::ostream& Log::info() {
	return log(INFO);
}

std::ostream& Log::warning() {
	return log(WARNING);
}

std::ostream& Log::error() {
	return log(ERROR);
}

Log::Log() : _level(ERROR) {
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
