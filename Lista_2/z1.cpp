#include <iostream>
#include <string>

namespace cpplab
{
    template <typename T1, typename T2>
    auto add(T1 *a, T2 *b) -> decltype(*a + *b)
    {
        return *a + *b;
    }

    template <typename T1, typename T2>
    std::enable_if_t<std::is_same<std::is_same<T1, const char*>::bool,std::is_same<T2, const char*>::bool >::value>
    add(T1 *a, T2 *b)
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
    std::cout << cpplab::add(c, d) << "\n";
    return 0;
}