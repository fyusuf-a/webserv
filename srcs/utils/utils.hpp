#ifndef UTILS_HPP
#define UTILS_HPP
#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <sstream>
#include <map>
#include "Log.hpp"

namespace Utils
{
	struct cmpCharInsensitive {
		bool operator() (const unsigned char a, const unsigned char b);
	};
	struct cmpStringInsensitive {
		bool operator()(const std::string&, const std::string&) const;
		static bool is_less(const std::string&, const std::string&);
		static bool is_equal(const std::string&, const std::string&);
	};
	bool is_equal_insensitive(const std::string&, const std::string&);
	std::string month_to_str(unsigned int i);
	std::string weekday_to_str(unsigned int i);
	std::ostream& print_date(std::ostream& os, bool show_weekday = true, bool show_gmt = true);

    bool is_space(char const c);
    bool is_spaces(std::string const s);
    bool is_valid_methods(std::string const &s);
    bool is_valid_directive(std::string const &dir);
    bool is_valid_directive_location(std::string const &dir);
    bool is_valid(std::string& str, std::string const& val);
    bool is_digits(std::string const &str);
    bool is_digit(char const c);
    bool is_file(const char *s);
    void ft_trim(std::string &str);
    bool is_comentary(std::string &str);

    //template <typename T>
    //bool is_set(std::vector<T> value);

    int ft_find(std::string str, std::string find);
    int is_dir(const char *name);
    std::string toString(int &i);

	bool set_fd_as_non_blocking(int fd, const char* fd_description);

	std::string find_mime_type(std::string& ext);
};

struct MyException : public std::exception
{
   std::string s;
   MyException(std::string ss) : s(ss) {}
   ~MyException() throw () {}
   const char* what() const throw() { return s.c_str(); }
};

template <typename T>
T list_front(std::list<T> list) {
	if (list.empty())
		throw std::out_of_range("empty list");
	return (*list.begin());
}

template <typename T>
T list_back(std::list<T> list) {
	if (list.empty())
		throw std::out_of_range("empty list");
	return (*(list.end() - 1));
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
	size_t	len = vec.size();
	for (size_t i = 0; i < len; i++)
		os << vec[i] << (i == len - 1 ? "" : ",");
	return os;
}

#endif
