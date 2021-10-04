#include "../../includes/parsingConf.hpp"

// Error makefile supprime pas les .o
//
//
//
//
//

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
    if (!line.compare(i, 6, "server"))
        i += 6;
    else
        return (false);
    while (line[i])
    {
        if (!Utils::is_space(line[i]))
            return (false);
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
            return (false);
        i++;
    }
    return (true);
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
            content.push_back(tmp);
            content.push_back("{");
            if (!line[i + 1])
                return content;
            line = &line[i + 1];
            i = -1;
        }
        else if (line[i] == '}')
        {
            tmp = line.substr(0, i);

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
        if (!line[i + 1])
        {
            content.push_back(line);
            return (content);
        }
    }
    return (content);
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
        return (false);
    while (line[i] && Utils::is_space(line[i]))
        i++;
    while (line[i] && line[i] != ';')
        value += line[i++];
    while(!value.empty() && Utils::is_space(*value.rbegin()))
        value.erase(value.size() - 1);
    return (true);
}



std::vector<std::string> ParsingConf::parsing_index_value(std::string val)
{
    std::vector<std::string> tab;

    for (int i = 0; i < val.size(); )
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
        {
            std::cerr << "[ERROR] Directive: '" << dir << "' syntaxe must be like ['method','method']" << std::endl;
            exit(1);
        }
        start = found + 1;
        found = val.find(",", start);
        len = found - start;

    }
    str = val.substr(start, val.size());

    if (!str.empty() && str[0] != ',')
        methods.push_back(str);
    else
    {
        std::cerr << "[ERROR] Directive: '" << dir << "' syntaxe must be like ['method','method']" << std::endl;
        exit(1);
    }
    // check if it's valid methods
    for (start = 0; start != methods.size(); )
    {
        Utils::ft_trim(methods[start]);
        if (Utils::is_valid(methods[start], "get") || Utils::is_valid(methods[start], "post"))
            start++;
        else
        {
            std::cerr << "[ERROR] Directive: Unknow value '" << methods[start] <<  "' : only 'get' & 'post' are available'" << std::endl;
            exit(1);
        }
    }
    return (methods);
}
std::string ParsingConf::parsing_bool_value(std::string str, std::string dir)
{
    if (Utils::is_valid(str, "on") || Utils::is_valid(str, "off"))
        return (str);
    else 
        std::cerr << "[ERROR] Directive: '" << dir << "'  : must be 'on' or 'off'" << std::endl;
    exit(1);
    return (NULL);
}
std::string ParsingConf::parsing_path_value(std::string str, std::string dir)
{
    int i = 0;
    std::string path;

    for (; i < str.size() && !Utils::is_space(str[i]); i++)
        path += str[i];

    if (i != str.size())
    {
        std::cerr << "[ERROR] Directive: '" << dir << "'  must have only 1 parameter" << std::endl;
        exit(1);
    }
    return (path);
}
std::string ParsingConf::parsing_cgi_ext_value(std::string str, std::string dir)
{
    int i = 0;
    std::string extention;

    for (; i < str.size() && !Utils::is_space(str[i]); i++)
        extention += str[i];
    if (!Utils::is_valid(extention, ".php"))
    {
        std::cerr << "[ERROR] Directive: '" << dir << "' : must be .php" << std::endl;
        exit(1);
    }
    return (extention);
}
int ParsingConf::parsing_digit_value(std::string val, std::string dir)
{
    if (!Utils::is_digits(val))
    {
        std::cerr << "[ERROR] Directive: '" <<  dir << "' : value must be digit with only 1 parameter" << std::endl;
        exit(1);
    }
    return ( std::atoi(val.c_str()) );
}
std::string ParsingConf::parsing_name_value(std::string val, std::string dir)
{
    for (int i = 0; val[i]; i++)
    {
        if (Utils::is_space(val[i]))
        {
            std::cerr << "[ERROR] Directive: '" <<  dir << "' : must have only 1 parameter" << std::endl;
            exit(1);
        }
    }
    return (val);
}


void  ParsingConf::setup_location_directive(std::string const &line, ServerLocation &location)
{
    std::string directive;
    std::string value;

    int i = parse_directive(line, directive);
    if (!Utils::is_valid_directive_location(directive))
    {
        std::cerr << "[ERROR] Directive: unknow directive " << directive << std::endl;
        exit(1);
    }
    else if (!parse_value(line, value, i))
    {
        std::cerr << "[ERROR] Directive: invalid parameter " << directive << std::endl;
        exit(1);
    }
    else
    {
        if (directive == "index")
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
}


void ParsingConf::setup_location(ITER &start, ITER &end, Server &server)
{
    ServerLocation location;
    for (; start != end;)
    {
        setup_location_directive(*start, location);
        if (start != end)
            start++;
    }
    server._locations.push_back(location);

}


void  ParsingConf::setup_others(std::string const &line, Server &server)
{
    std::string directive;
    std::string value;

    int i = parse_directive(line, directive);
    if (!Utils::is_valid_directive(directive))
    {
        std::cerr << "[ERROR] Directive: unknow directive " << directive << std::endl;
        exit(1);
    }
    else if (!parse_value(line, value, i))
    {
        std::cerr << "[ERROR] Directive: invalid parameter " << directive << std::endl;
        exit(1);
    }
    else
    {
        if (directive == "listen")
            server._serverConf.set_port( parsing_digit_value(value, directive) );
        else if (directive == "host")
            server._serverConf.set_host(value);
        else if (directive == "server_name")
            server._serverConf.set_name( parsing_name_value(value, directive) );
        else if (directive == "root")
            server._serverConf.set_root( parsing_path_value(value, directive) );
        else if (directive == "error")
            server._serverConf.set_error( parsing_path_value(value, directive) );
    }

}

void ParsingConf::setup_server(ITER &start, ITER &end, Servers &servers)
{
    Server  server;
    
    for (int brace = 0; start != end;)
    {
        if (is_location_block(*start))
        {
            start++;

			if ((*start).find('{') != std::string::npos)
					brace++, start++;
            else
            {
                std::cerr << "[ERROR] Directive: directive \"location\" has no opening \"{\"" << std::endl;
                exit(1);
            }
            ITER block_start = start;
            while (start != end)
            {
                if ((*start).find('{') != std::string::npos)
					brace++;
                if ((*start).find('}') != std::string::npos)
					brace--;
                start++;
            }
            if (brace == 0)
                setup_location(block_start, --start, server);
            else
			{
				std::cerr << "[ERROR] Directive: ParsingConfuration parsing failure: missing \"}\"" << std::endl;
				exit(1);
			}
        }
        else
            setup_others(*start, server);
        if (start != end)
            start++;
    }
    servers.push_back(server);

}

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
            {
                std::cerr << "[ERROR] Directive: directive \"server\" has no opening \"{\"" << std::endl;
                exit(1);
            }
            ITER block_start = it;
            while (it != content.end())
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
			{
				std::cerr << "[ERROR] Directive: ParsingConfuration parsing failure: missing \"}\"" << std::endl;
				exit(1);
			}
        }
        if (it != content.end())
            it++;
    }
}

int ParsingConf::parsing(std::string path, Servers &servers)
{
    std::string                 line;
    std::vector<std::string>    content;
    std::ifstream               fd(path.c_str());

    if (!fd.is_open() && !fd.good())
        std::cerr << "[ERROR] File: Can't open File !" << std::endl;
    else
    {
        while (std::getline(fd, line))
            content = parsing_line(line, content);
        // delete all empty lines
        for (ITER it = content.begin(); it != content.end(); it++)
            if (Utils::is_spaces(*it))
                content.erase(it);

        this->setup_servers(content, servers);
    }
    return (1);
}