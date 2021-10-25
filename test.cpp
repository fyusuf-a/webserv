#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


class go
{
    public:
        int n;

    go() : n(1){std::cout << "constructor " << std::endl;};
    go(go const &o){std::cout << "copy constructor " << std::endl;}
    ~go(){std::cout << "destructor " << std::endl;};

    int get(void){return this->n;}
    void set(int n){this->n = n;}
};

class conf
{
    public:

        std::vector<std::string> t;
        go tt;

    conf()  {std::cout << "before  " << std::endl;};
    conf(conf const &o){std::cout << "here " << std::endl;}

    std::vector<std::string> get(void){return this->t;}
    void set(std::vector<std::string> n){this->t = n;}
};

bool is_set(std::vector<std::string> value)
{
    if (value.empty())
    {
        std::cout << "lalala" << std::endl;
        return (false);
    }
    return (true);

}



int main()
{
    conf test;
    std::vector<std::string> t;
    
    t.push_back("bonjour");

    test.set(t );

    if (is_set(test.get()) )
        std::cout << "prout " <<std::endl;
    else
        std::cout << "bonjr" <<std::endl;





    return 0;
}