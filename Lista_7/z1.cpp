#include <vector>
#include <iostream>
#include <functional>
#include <thread>

namespace cpplab
{
    class ThreadPool
    {
        public:
        ThreadPool()
        {
            
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