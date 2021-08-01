#include <iostream>
#include "src/Delegate.h"

void print(int i)
{
    std::cout << i;
}

int main()
{
    Delegate<int> del;
    del.Add(print);
    del.Invoke(3);
    return 0;
}
