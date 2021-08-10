#include <iostream>
#include "src/Delegate.h"

void print(int i)
{
    std::cout << i;
}

class my
{
public:
    void function(int a) const
    {

    }
};

int main()
{
    std::function<void(int)> a = nullptr;
    if (a)
    {
        std::cout << "a";
    }
    Delegate<int, const std::string&> delegate;
    delegate.Add([](int a, const std::string& b){

    });
    delegate.Invoke(1, "sdf");
    return 0;
}
