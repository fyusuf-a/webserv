#include "../../includes/parsingConf.hpp"

ParsingConf::ParsingConf(){}

ParsingConf::ParsingConf(const ParsingConf &other){(void)other;}

ParsingConf::~ParsingConf(){}

ParsingConf &ParsingConf::operator=(const ParsingConf &other)
{
    if (this != &other)
    {}
    return (*this);
}


bool ParsingConf::is_serv_block(std::string const &line)
{
    int i = 0;

    while (line[i] && Utils::is_space(line[i]))
        i++;
    if (!line.compare(i, 6, "server") && line.compare(i, 7, "server_"))
        i += 6;
    else
        return (false);
    while (line[i])
    {
        if (!Utils::is_space(line[i]))
            throw MyException("Server block line : Expected - [server]");
        i++;
    }
    return (true);
}
bool ParsingConf::is_location_block(std::string const &line)
{
    int i = 0;
    
    while (line[i] && Utils::is_space(line[i]))
        i++;
    if (!line.compare(i, 8, "location"))
        i += 8;
    else
        return (false);
    while (line[i])
    {
        if (!Utils::is_space(line[i]))
            throw MyException("Location block line : Expected - [location]");
        i++;
    }
    return (true);
}



int ParsingConf::parse_directive(std::string const &line, std::string &directive)
{
    int i = 0;

    while (line[i] && Utils::is_space(line[i]))
        i++;
    while (line[i] && !Utils::is_space(line[i]))
        directive += line[i++];
    return (i);
}
bool ParsingConf::parse_value(std::string const &line, std::string &value, int i)
{
    if (line[line.size() - 1] != ';')
        throw MyException("Line must finish by ';'");
    while (line[i] && Utils::is_space(line[i]))
        i++;
    while (line[i] && line[i] != ';')
        value += line[i++];
    return (true);
}


// ---- [Parsing Value] ----- 
std::vector<std::string> ParsingConf::parsing_index_value(std::string val)
{
    std::vector<std::string> tab;

    for (size_t i = 0; i < val.size(); )
    {
        std::string tmp;

        while (val[i] && !Utils::is_space(val[i]))
            tmp += val[i++];

        tab.push_back(tmp);
        
        while (val[i] && Utils::is_space(val[i]))
            i++;
    }
    return (tab);
}
std::vector<std::string> ParsingConf::parsing_methods_value(std::string val, std::string dir)
{
    std::string str;
    std::vector<std::string> methods;

    size_t start = 0;
    size_t found = val.find(",", start);
    size_t len = found;


    // check syntaxe and stock it in Vector
    while (found != std::string::npos)
    {
        str = val.substr(start, len);

        if (!str.empty() && str[0] != ',')
            methods.push_back(str);
        else
            throw MyException("Directive: '" +  dir + "' : Expected - [get,post , delete]'");
        start = found + 1;
        found = val.find(",", start);
        len = found - start;

    }
    str = val.substr(start, val.size());

    if (!str.empty() && str[0] != ',')
        methods.push_back(str);
    else
            throw MyException("Directive: '" +  dir + "' : Expected - [get,post , delete]'");
    // check if it's valid methods
    for (start = 0; start != methods.size(); )
    {
        Utils::ft_trim(methods[start]);
        if (Utils::is_valid(methods[start], "get") || Utils::is_valid(methods[start], "post") || Utils::is_valid(methods[start], "delete"))
            start++;
        else
            throw MyException("Directive: '" +  dir + "' : Expected - [get,post , delete]'");
    }
    return (methods);
}
std::string ParsingConf::parsing_bool_value(std::string str, std::string dir)
{
    if (Utils::is_valid(str, "on") || Utils::is_valid(str, "off"))
        return (str);
    else 
        throw MyException("Directive: '" +  dir + "'  : Expected - [on | off]'");
    return (NULL);
}
std::string ParsingConf::parsing_path_value(std::string str, std::string dir)
{
    size_t i = 0;
    std::string path;

    Utils::ft_trim(str);

    for (; i < str.size() && !Utils::is_space(str[i]); i++)
        path += str[i];

    if (i != str.size())
        throw MyException("Directive: '" +  dir + "'  Expected - [my/path/example.test]");
    return (path);
}
std::string ParsingConf::parsing_cgi_ext_value(std::string str, std::string dir)
{
    size_t i = 0;
    std::string extention;

    for (; i < str.size() && !Utils::is_space(str[i]); i++)
        extention += str[i];
    if (!Utils::is_valid(extention, ".php"))
        throw MyException("Directive: '" +  dir + "'  Expected - [test.php]");
    return (extention);
}
int ParsingConf::parsing_digit_value(std::string val, std::string dir)
{
    int value;

    if (!Utils::is_digits(val))
        throw MyException("Directive: '" +  dir + "' : Expected - [1 digit parameter]");
    
    value = ::atoi(val.c_str());
    
    if (value < 0 || value > 65535)
        throw MyException("Directive: '" +  dir + "' : Expected - [1 digit parameter]" );

    return ( ::atoi(val.c_str()) );
}
std::string ParsingConf::parsing_name_value(std::string val, std::string dir)
{
    for (int i = 0; val[i]; i++)
    {
        if (Utils::is_space(val[i]))
            throw MyException("Directive: '" +  dir + "' : Expected - [my_name]");
    }
    return (val);
}
uint32_t    ParsingConf::parsing_host_value(std::string val, std::string dir)
{
    uint32_t result = 0;

    std::istringstream iss(val);

    for (int i = 0; i < 4; ++i)
    {
        uint32_t tmp;

        iss >> tmp;
        
        if (iss.fail() || tmp > 255)
            throw MyException("Directive: '" +  dir + "' : invalid IP adress - Must be [0 - 255]");

        result |= tmp << (8  * (3 - i));

        if (i < 3)
        {
            char c;

            iss >> c;
            if (iss.fail() || c != '.')
                throw MyException("Directive: '" +  dir + "' : IP must have '.' delimiter");
        }
    }
    return (result);
}    


// SET ALL LOCATION AND SERVER INFOS FOR EACH BLOCK
void  ParsingConf::setup_location_directive(std::string const &line, ServerLocation &location)
{
    std::string directive;
    std::string value;

    int i = parse_directive(line, directive);
    if (Utils::is_valid_directive(directive) && directive != "index")
        throw MyException("Directive: '" +  directive + "' : Only allowed in server block");

    if (!Utils::is_valid_directive_location(directive))
        throw MyException("Directive: '" +  directive + "' : Unknow");

    parse_value(line, value, i);

    if (directive == "index" /*&& Utils::is_set()*/)
        location.set_index( parsing_index_value(value) );
    else if (directive == "methods")
        location.set_methods( parsing_methods_value(value, directive) );
    else if (directive == "cgi_extension")
        location.set_cgi_ext( parsing_cgi_ext_value(value, directive) );
    else if (directive == "cgi_bin")
        location.set_cgi_bin( parsing_path_value(value, directive) );
    else if (directive == "language") // language a faire
        location.set_language(value); // ----------------
    else if (directive == "autoindex")
        location.set_auto_index( parsing_bool_value(value, directive) );
    else if (directive == "auth_basic")
        location.set_auth_basic( parsing_bool_value(value, directive) );
    else if (directive == "auth_basic_user_file")
        location.set_auth_basic_file( parsing_path_value(value, directive) );
    else if (directive == "client_max_body_size")
        location.set_body_size( parsing_digit_value(value, directive) );
}
void  ParsingConf::setup_server_directive(std::string const &line, Server &server)
{
    std::string directive;
    std::string value;

    int i = parse_directive(line, directive);
    if (Utils::is_valid_directive_location(directive) && directive != "index")
        throw MyException("Directive: '" +  directive + "' : only Allowed in location block");

    else if (!Utils::is_valid_directive(directive))
        throw MyException("Directive: '" +  directive + "' : Unknow");

    else if (!parse_value(line, value, i))
        throw MyException("Directive: '" +  directive + "' : Invalid parameter");
        
    else
    {
        if (directive == "listen")
            server._serverConf.set_port( parsing_digit_value(value, directive) );
        else if (directive == "host")
            server._serverConf.set_host( parsing_host_value(value, directive) );
        else if (directive == "server_name")
            server._serverConf.set_name( parsing_name_value(value, directive) );
        else if (directive == "root")
            server._serverConf.set_root( parsing_path_value(value, directive) );
        else if (directive == "error")
            server._serverConf.set_error( parsing_path_value(value, directive) );
    }

}



void ParsingConf::setup_location(ITER &start, ITER &end, Server &server)
{
    ServerLocation location;

    for (; start != end;)
    {
        if (is_location_block(*start) || is_serv_block(*start))
            throw MyException("Directive: 'location' : Not allowed here");

        setup_location_directive(*start, location);
        if (start != end)
            start++;
    }
    server._locations.push_back(location);
}
void ParsingConf::setup_server(ITER &start, ITER &end, Servers &servers)
{
    Server  server;

    for (int brace = 0; start != end;)
    {
        if (is_serv_block(*start))
            throw MyException("Directive: 'server' : Not allowed here");

        if (is_location_block(*start))
        {
            start++;

			if ((*start).find('{') != std::string::npos)
					brace++, start++;
            else
                throw MyException("Directive: \"location\" has no opening \"{\"");

            ITER block_start = start;

            while (start != end && brace != 0)
            {
                if ((*start).find('}') != std::string::npos)
					brace--;
                start++;
            }
            if (brace == 0)
                setup_location(block_start, --start, server);
            else
                throw MyException("ParsingConfuration parsing failure: missing \"}\"");
        }
        else
            setup_server_directive(*start, server);
        if (start != end)
            start++;
    }
    servers.push_back(server);
}




// Call the "setup_server()" fonction for each server block 
void ParsingConf::setup_servers(std::vector<std::string> &content, Servers &servers)
{
    int brace = 0;
    for (ITER it = content.begin(); it != content.end();)
    {
        if (is_serv_block(*it))
        {
            it++;
			if ((*it).find('{') != std::string::npos)
					brace++, it++;
            else
                throw MyException("Directive: \"server\" has no opening \"{\"");

            ITER block_start = it;
            while (it != content.end() && brace != 0)
            {
                if ((*it).find('{') != std::string::npos)
                    brace++;
                if ((*it).find('}') != std::string::npos)
					brace--;
                it++;
            }
            if (brace == 0)
                setup_server(block_start, --it, servers);
            else
                throw MyException("ParsingConfuration parsing failure: missing \"}\"");
        }
        else
            throw MyException("'" + *it  + "' : line not expected here");
        if (it != content.end())
            it++;
    }

}



// split the conf file by ';' & "{,}"
std::vector<std::string> ParsingConf::parsing_line(std::string line, std::vector<std::string> content)
{
    std::string tmp;

    for (int i = 0; line[i]; i++)
    {
        if (line[i] == '{')
        {
            tmp = line.substr(0, i);
            if (!Utils::is_spaces(tmp) || tmp.empty())
                content.push_back(tmp);

            content.push_back("{");
            if (!line[i + 1])
            {
                return content;
            }
            line = &line[i + 1];
            i = -1;
        }
        else if (line[i] == '}')
        {
            tmp = line.substr(0, i);
            if (!Utils::is_spaces(tmp) || tmp.empty())
                content.push_back(tmp);
            content.push_back("}");
            if (!line[i + 1])
                return content;
            line = &line[i + 1];
            i = -1;
        }
        else if (line[i] == ';')
        {
            tmp = line.substr(0, i + 1);
            content.push_back(tmp);
            if (!line[i + 1])
                return content;
            line = &line[i + 1];
            i = -1;
        }
        if (!line[i + 1] && (!Utils::is_spaces(line) && tmp.empty()))
        {
            content.push_back(line);
            return (content);
        }
    }
    return (content);
}

void ParsingConf::parsing(std::string path, Servers &servers)
{
    std::string                 line;
    std::vector<std::string>    content;
    std::ifstream               fd(path.c_str());

    if (!fd.is_open() && !fd.good())
        throw MyException("[ERROR] File: Can't open File !");
    else
    {
        while (std::getline(fd, line))
            content = parsing_line(line, content);
        if (content.empty())
            throw MyException("[ERROR] File: Empty");

        // delete all empty lines
        for (ITER it = content.begin(); it != content.end();)
        {
            Utils::ft_trim(*it);

            if (Utils::is_comentary(*it) || (Utils::is_spaces(*it) && (*it).empty()))
                content.erase(it);
            else
                it++;
        }

        this->setup_servers(content, servers);
    }
}
