#include <vector>
#include <iostream>
#include <functional>
#include <thread>

namespace cpplab
{
    class ThreadPool
    {
        public:
        ThreadPool(size_t threads_count)
        {
            for (int i = 0; i < threads_count; ++i)
                threads.emplace_back(std::thread());
        }

        void add_task(std::function<double()> task)
        {
            threads.emplace_back(task);
        }
        private:
        std::vector<std::function<double()>> task_vector;
        std::vector<std::thread> threads;
    };
}

int main()
{
    
}