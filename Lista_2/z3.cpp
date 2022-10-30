#include <iostream>

namespace cpplab
{
    template <typename Head, typename... Tail>
    auto add_total(Head head, Tail... tail)
    {
        if constexpr (sizeof...(tail) == 0)
            return head;
        else
            return head + add_total(tail...);
    }
}

int main()
{
    std::cout << cpplab::add_total(1, 2.5f, 3.8);
    return 0;
}