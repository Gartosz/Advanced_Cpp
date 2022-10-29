#include <iostream>

namespace cpplab
{
    template<typename T>
    auto add_total(T *arg)
    {
        std::cout << sizeof(arg);
    }
}

int main()
{
    cpplab::add_total(1, 1.0f, 1.0);
    
}