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
        private:
        std::vector<std::function<double()>> task_vector;
        std::vector<std::thread> threads;
    };
}

int main()
{
    
}