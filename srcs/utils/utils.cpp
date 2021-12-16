#include "utils.hpp"
#include <iomanip>


namespace Utils
{
	std::string month_to_str(unsigned int i) {
		static std::map<char, std::string> month_to_str;
		if (month_to_str.empty()) {
			month_to_str[0] = "Jan";
			month_to_str[1] = "Feb";
			month_to_str[2] = "Mar";
			month_to_str[3] = "Apr";
			month_to_str[4] = "May";
			month_to_str[5] = "Jun";
			month_to_str[6] = "Jul";
			month_to_str[7] = "Aug";
			month_to_str[8] = "Sep";
			month_to_str[9] = "Oct";
			month_to_str[10] = "Nov";
			month_to_str[11] = "Dec";
		}
		if (i > 11)
			return "";
		return month_to_str[i];
	}

	std::string weekday_to_str(unsigned int i) {
		static std::map<char, std::string> weekday_to_str;
		if (weekday_to_str.empty()) {
			weekday_to_str[0] = "Mon";
			weekday_to_str[1] = "Tue";
			weekday_to_str[2] = "Wed";
			weekday_to_str[3] = "Thu";
			weekday_to_str[4] = "Fri";
			weekday_to_str[5] = "Sat";
			weekday_to_str[6] = "Sun";
		}
		if (i > 11)
			return "";
		return weekday_to_str[i];
	}

	std::ostream & print_date(std::ostream& os, bool show_weekday, bool show_gmt) {
		time_t rawtime;
		time(&rawtime);
		struct tm* t = localtime(&rawtime);
		if (show_weekday)
			os << weekday_to_str(t->tm_wday) << ", ";
		os << std::setfill('0') << std::setw(2) << t->tm_mday << " "
			<< std::setfill('0') << std::setw(2) << month_to_str(t->tm_mon)
			<< " " << std::setw(4) << (1900 + t->tm_year) << " " 
			<< std::setfill('0') << std::setw(2) << t->tm_hour << ":"
			<< std::setfill('0') << std::setw(2) << t->tm_min << ":"
			<< std::setfill('0') << std::setw(2) << t->tm_sec;
		if (show_gmt)
			os << " GMT";
		return os;
	}

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
        size_t i = 0;
        for (; str[i] == find[i]; i++);

        if (i < str.size())
            return (0);
        return (i);
    }

    bool         is_file(const char *path) 
    {
        struct stat s;

        if (!stat(path, &s) && !(s.st_mode & S_IFDIR))
                return (true);
         return (false);
    }
    int is_dir(const char *name)
    {
        int ret = 0;
        DIR* rep = opendir(name);
        
        if(rep != NULL)
        {
            closedir(rep);
            ret = 1;
        }
    
        return ret;
    }

    std::string toString(int &i)
    {
        std::stringstream ss;
        ss << i;
        return ss.str();
    }
}

