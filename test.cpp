#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class conf
{
    public:

    int nb;

    conf() : nb(0){};
        int get(void){return nb;}
    void set(int n){this->nb = n;}
};

class test
{
    public:
        conf _conf;
    test() : _conf(){};

};

void setup_server(test &ser)
{
    ser._conf.set(19);
}

void go()
{
                std::vector<test> tab;
                test server;

                setup_server(server);

                std::cout << server._conf.get() << std::endl;
                tab.push_back(server);
                std::cout << tab[0]._conf.get() << std::endl;

}

int main()
{
    std::string str = "post, get  , get";

    std::string st = str.substr(5, 11);
    std::cout << st << std::endl;
    return 0;
}