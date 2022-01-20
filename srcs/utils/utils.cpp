#include "utils.hpp"
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <fcntl.h>


namespace Utils
{
	bool cmpCharInsensitive::operator() (const unsigned char a, const unsigned char b) {
		return ::tolower(a) < tolower(b);
	}
	bool cmpStringInsensitive::operator()(const std::string& a, const std::string& b) const {
		return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(), cmpCharInsensitive());
	}

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
			weekday_to_str[0] = "Sun";
			weekday_to_str[1] = "Mon";
			weekday_to_str[2] = "Tue";
			weekday_to_str[3] = "Wed";
			weekday_to_str[4] = "Thu";
			weekday_to_str[5] = "Fri";
			weekday_to_str[6] = "Sat";
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
        if (dir == "index" || dir == "root" || dir == "server_name"
        || dir == "listen" || dir == "host" || dir == "error"
        || dir == "cgi_extension" || dir == "cgi_bin")
            return (true);
        return (false);
    }
    bool is_valid_directive_location(std::string const &dir)
    {
        if (dir == "index" || dir == "methods" || dir == "cgi_extension"
        || dir == "cgi_bin" || dir == "language" || dir == "autoindex" || dir == "root"
        || dir == "client_max_body_size" || dir == "auth_basic" || dir == "auth_basic_user_file" || dir == "redirection")
            return (true);
        return (false);
    }
    bool is_valid_methods(std::string const &dir)
    {
        if (dir == "GET" || dir == "POST" || dir == "DELETE")
            return (true);
        return (false);
    }
    bool is_valid(std::string& str, std::string const& val)
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

	bool set_fd_as_non_blocking(int fd, const char* fd_description) {
		if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
		{
			Log::getInstance().error() << "cannot set " << fd_description << " as nonblocking" << std::endl;
			return false;
		}
		return true;
	}

    std::size_t find_value(char val) {
        std::string base1 = "0123456789ABCDEF";
        std::string base2 = "0123456789abcdef";

        if (!val)
            throw (400);
        if (base1.find(val) != std::string::npos)
            return (base1.find(val));
        else if (base2.find(val) != std::string::npos)
            return (base2.find(val));
        throw (400);
    }

    std::string percent_decode(const std::string str) {
        std::string decoded;
        std::size_t i = 0;
        char ascii;

        while (str[i]) {
            if (str[i] != '%')
                decoded += str[i];
            else {
                ascii = 0;
                i++;
                ascii += find_value(str[i]) * 16;
                i++;
                ascii += find_value(str[i]);
                decoded += ascii;
            }
            i++;
        }
        return (decoded);
    }
    
    std::string percent_encode(const std::string str) {
        std::string encoded;
        std::size_t i = 0;
        int first_dig = 0;
        std::string base = "0123456789ABCDEF";
        char c;

        while (str[i]) {
            c = str[i];
            if (c != '!' && (c < '#' || c > ',') && c != '/' && c != ':' && c != ';' && c != '=' && c != '?' && c != '@' && c != '[' && c != ']')
                encoded += str[i];
            else {
                encoded += '%';
                first_dig = str[i] / 16;
                encoded += base[first_dig];
                encoded += base[str[i] - first_dig * 16];
            }
            i++;
        }
        return (encoded);
    }
}

