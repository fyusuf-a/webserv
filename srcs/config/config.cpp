#include "../../includes/config.hpp"

Config::Config(){}

Config::Config(const Config &other){}

Config::~Config(){}

Config &Config::operator=(const Config &other)
{
    if (this != &other)
    {}
    return (*this);
}

bool Config::is_serv_block(std::string const &line)
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
bool Config::is_location_block(std::string const &line)
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
std::vector<std::string> Config::parsing_line(std::string line, std::vector<std::string> content)
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

bool is_valid_directive(std::string const &dir)
{
    if (dir == "index" || dir == "root" || dir == "server_name" || dir == "listen" || dir == "host")
        return (true);
    return (false);
}

int Config::parse_directive(std::string const &line, std::string &directive)
{
    int i = 0;

    while (line[i] && Utils::is_space(line[i]))
        i++;
    while (line[i] && !Utils::is_space(line[i]))
        directive += line[i++];
    return (i);
}

bool Config::parse_value(std::string const &line, std::string &value, int i)
{
    if (line[line.size() - 1] != ';')
        return (false);
    while (line[i] && Utils::is_space(line[i]))
        i++;
    while (line[i] && !Utils::is_space(line[i]) && line[i] != ';')
        value += line[i++];
    return (true);
}

void Config::setup_location(ITER &start, ITER &end)
{
    // std::string directive;
    // std::string value;

    // int i = parse_directive(line, directive);
    // if (!is_valid_directive(directive))
    // {
    //     std::cout << "unknow directive " << directive << std::endl;
    //     exit(1);
    // }
    // else if (!parse_value(line, value, i))
    // {
    //     std::cout << "invalid parameter " << directive << std::endl;
    //     exit(1);
    // }
}


void  Config::setup_others(std::string const &line, Server &server)
{
    std::string directive;
    std::string value;

    int i = parse_directive(line, directive);
    if (!is_valid_directive(directive))
    {
        std::cout << "unknow directive " << directive << std::endl;
        exit(1);
    }
    else if (!parse_value(line, value, i))
    {
        std::cout << "invalid parameter " << directive << std::endl;
        exit(1);
    }
    else
    {
        if (directive == "listen")
            server._serverConf.set_port( std::atoi(value.c_str()) );
        else if (directive == "host")
            server._serverConf.set_host(value);
        else if (directive == "server_name")
            server._serverConf.set_name(value);
        else if (directive == "root")
            server._serverConf.set_root(value);
    }

}

void Config::setup_server(ITER &start, ITER &end, Servers &servers)
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
                std::cout << "directive \"location\" has no opening \"{\"" << std::endl;
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
                setup_location(block_start, --start);
            else
			{
				std::cout << "Configuration parsing failure: missing \"}\"" << std::endl;
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

void Config::setup_servers(std::vector<std::string> &content, Servers &servers)
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
                std::cout << "directive \"server\" has no opening \"{\"" << std::endl;
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
				std::cout << "Configuration parsing failure: missing \"}\"" << std::endl;
				exit(1);
			}

                
        }
        if (it != content.end())
            it++;
    }
}

int Config::parsing(std::string path, Servers &servers)
{
    std::string                 line;
    std::vector<std::string>    content;
    std::ifstream               fd(path.c_str());

    if (!fd.is_open() && !fd.good())
        std::cerr << "Can't open File !" << std::endl;
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