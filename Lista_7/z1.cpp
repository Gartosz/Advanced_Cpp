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

        ~ThreadPool()
        {

        }

        void add_task(std::function<double()> task)
        {
            threads.emplace_back(task);
        }

        double average()
        {
            
        }

        void stop()
        {
            
        }

        private:
        std::vector<std::function<double()>> task_vector;
        std::vector<std::thread> threads;
    };
}

int main()
{
    
}