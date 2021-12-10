#include "Log.hpp"
#include "utils.hpp"

void Log::setLevel(log_level_t level) {
	_level = level;
}

std::ostream& Log::log(log_level_t level) {
	if (level < _level)
		return _nullStream;
	std::cout << "[";
	Utils::print_date(std::cout, false, false);
	std::cout << " " <<  std::setfill(' ') << std::setw(7)
		<< _levels_to_str[level] << "] ";
	return std::cout;
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

Log::Log() : _level(ERROR), _nullStream(&_nullBuffer) {
	_levels_to_str[DEBUG] = "debug";
	_levels_to_str[INFO] = "info";
	_levels_to_str[WARNING] = "warning";
	_levels_to_str[ERROR] = "error";
}
