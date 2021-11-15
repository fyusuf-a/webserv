#ifndef UTILS_HPP
#define UTILS_HPP
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>


namespace Utils
{
    bool is_space(char const c);
    bool is_spaces(std::string const s);
    bool is_valid_methods(std::string const &s);
    bool is_valid_directive(std::string const &dir);
    bool is_valid_directive_location(std::string const &dir);
    bool is_valid(std::string  &str, std::string const val);
    bool is_digits(std::string const &str);
    bool is_digit(char const c);

    void ft_trim(std::string &str);
    bool is_comentary(std::string &str);


    // bool is_set(std::string value);
    template <typename T>
    bool is_set(std::vector<T> value);

    int ft_find(std::string str, std::string find);





};

struct MyException : public std::exception
{
   std::string s;
   MyException(std::string ss) : s(ss) {}
   ~MyException() throw () {}
   const char* what() const throw() { return s.c_str(); }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
	size_t	len = vec.size();
	for (size_t i = 0; i < len; i++)
		os << vec[i] << (i == len - 1 ? "" : ",");
	return os;
}



#endif
