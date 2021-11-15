#include "utils.hpp"


namespace Utils
{
    bool is_space(char c)
    {
        if ((c >= 9 && c <= 13) || c == 32 || c == '\t')
            return (true);
        return (false);
    }
    bool is_spaces(std::string const s)
    {
        for (int i =  0; s[i]; i++)
            if (!is_space(s[i]))
                return (false);
        return (true);
    }
    bool is_valid_directive(std::string const &dir)
    {
        if (dir == "index" || dir == "root" || dir == "server_name" || dir == "listen" || dir == "host" || dir == "error")
            return (true);
        return (false);
    }
    bool is_valid_directive_location(std::string const &dir)
    {
        if (dir == "index" || dir == "methods" || dir == "cgi_extension"
        || dir == "cgi_bin" || dir == "language" || dir == "autoindex" || dir == "root"
        || dir == "client_max_body_size" || dir == "auth_basic" || dir == "auth_basic_user_file")
            return (true);
        return (false);
    }
    bool is_valid_methods(std::string const &dir)
    {
        if (dir == "GET" || dir == "POST" || dir == "DELETE")
            return (true);
        return (false);
    }
    bool is_valid(std::string &str, std::string const val)
    {
        size_t found;

        found = str.find(val);
        if (found != std::string::npos)
        {
            for (size_t i = val.size(); i != str.size(); i++)
                if (!Utils::is_space(str[i]))
                    return (false);
            str = val;
            return (true);
        }
        return (false);
    }
    bool is_digit(char const c)
    {
        if (c >= '0' && c <= '9')
            return (true);
        return (false); 
    }
    bool is_digits(std::string const &str)
    {
        for (int i =  0; str[i]; i++)
            if (!is_digit(str[i]) && str[i] != '-')
                return (false);
        return (true);
    }
    void ft_trim(std::string &str)
    {
        while(!str.empty() && std::isspace(*str.begin()))
            str.erase(str.begin());
        
        while (!str.empty() && Utils::is_space(*str.rbegin()))
            str.erase(str.size() - 1);
    }
    bool is_comentary(std::string &str)
    {
        size_t i = str.find("#", 0);

        if (i == 0)
        {
            return (true);
        }
        if (i != std::string::npos)
        {
            str.erase(i, str.size());

            return (false);
        }
        else
            return (false);
        return (true);
    }
    int ft_find(std::string str, std::string find)
    {
        int i = 0;
        for (; str[i] == find[i]; i++);
        return (i);
    }


    bool DoesFileExist (const std::string& name)
    {
        return ( access( name.c_str(), F_OK ) != -1 );
    }
}

