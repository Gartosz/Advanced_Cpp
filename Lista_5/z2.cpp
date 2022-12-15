#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <future>

namespace cpplab
{
    int get_id()
    {
        static int global_id = 0;
        static std::mutex mutex;
        const std::lock_guard<std::mutex> lock(mutex);
        thread_local int thread_id = global_id++;
        return thread_id;
    }

    void print(std::string const &text)
    {
        static std::mutex mutex;
        const std::lock_guard<std::mutex> lock(mutex);
        std::cout << get_id() << " " << text << "\n";
    }

    void async_run(std::launch launch_option, std::string message, int counter)
    {
        if (--counter >= 0)
        {
            auto async_1 = std::async(launch_option, async_run, launch_option, message, counter);
            print(message);
            async_1.get();
        }
    }
    }

int main()
{
    cpplab::async_run(std::launch::async, "ASYNC", 10);
    cpplab::async_run(std::launch::deferred, "DEFERRED", 10);
    return 0;
}