#include <vector>
#include <iostream>
#include <functional>

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
    };
}

int main()
{
    
}