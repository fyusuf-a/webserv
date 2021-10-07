#ifndef UTILS_HPP
#define UTILS_HPP
#include <vector>
#include <string>
#include <iostream>
#include <fstream>


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






};


#endif