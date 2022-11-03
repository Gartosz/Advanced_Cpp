#include <iostream>

namespace cpplab
{
    template <typename F, typename... R>
    auto add_total(F first, R... remaining)
    {
        if constexpr (sizeof...(remaining) == 0)
            return first;
        else
            return first + add_total(remaining...);
    }
}

int main()
{
    std::cout << cpplab::add_total(1, 2.5f, 3.8);
    return 0;
}