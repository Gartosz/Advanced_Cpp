#include <iostream>
#include <concepts>

namespace cpplab
{
    template <typename T1, typename T2>
    auto add(T1 *a, T2 *b) -> decltype(*a + *b)
    {
        return *a + *b;
    }

    template<std::same_as<const char*> T1, std::same_as<const char*> T2>
    auto add(T1 a, T2 b)
    {
        return std::string(a) + std::string(b);
    }
}

int main()
{
    int a = 10, b = 4;
    float f = 2.59;
    const char *c = "cpp", *d = "lab";
    std::cout << cpplab::add(&a, &b) << "\n";
    std::cout << cpplab::add(&f, &b) << "\n";
    std::cout << cpplab::add<const char*>(c, d) << "\n";
    return 0;
}