#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


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
    uint32_t result = 0;

    std::istringstream iss("1");

        uint32_t tmp;

        iss >> tmp;
        
        result |= tmp << (8 * 3);

      std::cout << result << std::endl;
}    




int main()
{
    go();
    return 0;
}