#include "../../includes/utils.hpp"


namespace Utils
{
    bool is_space(char c)
    {
        if ((c >= 9 && c <= 13) || c == 32)
            return (true);
        return (false);
    }
    bool is_spaces(std::string s)
    {
        for (int i =  0; s[i]; i++)
            if (!is_space(s[i]))
                return (false);
        return (true);
    }
}