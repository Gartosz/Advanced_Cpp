#include <iostream>
#include <thread>
#include <string>

namespace cpplab
{
    int get_id()
    {
        thread_local int thread_id = -1;
        return thread_id;
    }
    void print(std::string const &text)
    {
        std::cout << get_id() << " " << text << "\n";
    }
}

int main()
{
    std::thread th_1(cpplab::print, "Serwus");
    std::thread th_2(cpplab::print, "Serwus");
    std::thread th_3(cpplab::print, "Serwus");
    std::thread th_4(cpplab::print, "Serwus");

    th_1.join();
    th_2.join();
    th_3.join();
    th_4.join();
    return 0;
}