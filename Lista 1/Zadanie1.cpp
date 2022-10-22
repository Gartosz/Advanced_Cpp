#include <iostream>
#include <string>

namespace cpplab
{
    template<typename T1, typename T2>
    auto add(T1 const& var_1, T2 const& var_2) -> decltype(var_1 + var_2)
    {
        return var_1+var_2;
    }

    template<typename T1, typename T2, typename T3>
    auto alias(T1 const& var_1, T2 const& var_2, T3 operation) -> decltype(operation(var_1, var_2))
    {
        return operation(var_1, var_2);
    }

}

int main()
{
    std::cout<<cpplab::add(1,5)<<"\n";
    std::cout<<cpplab::add(2.5,14.9)<<"\n";
    std::cout<<cpplab::add(2,7.3)<<"\n";
    std::cout<<cpplab::add("dada",2)<<"\n";
    std::cout<<cpplab::add(std::string("dada"),std::string("4gsgr"))<<"\n";
    
    std::cout<<cpplab::alias(1, 5.2, [](auto a, auto b) {return a<b?b:a;})<<"\n";
    std::cout<<cpplab::alias("asd", "bht", [](auto a, auto b) {return a<b?b:a;})<<"\n";
    std::cout<<cpplab::alias(3, 17, [](auto a, auto b) {return a-b;})<<"\n";
    std::cout<<cpplab::alias(9.4, -6, [](auto a, auto b) {return a-b;})<<"\n";

    return 0;
}