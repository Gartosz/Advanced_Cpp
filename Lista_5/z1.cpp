#include <iostream>
#include <thread>
#include <mutex>
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
        static std::mutex mutex;
        const std::lock_guard<std::mutex> lock(mutex);
        std::cout << get_id() << " " << text << "\n";
    }
}

int main()
{
    std::thread th_1(cpplab::print, "Serwus, ");
    std::thread th_2(cpplab::print, "Zimno");
    std::thread th_3(cpplab::print, "na");
    std::thread th_4(cpplab::print, "dworze");

    th_1.join();
    th_2.join();
    th_3.join();
    th_4.join();
    return 0;
}