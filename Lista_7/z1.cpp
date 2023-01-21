#include <vector>
#include <iostream>
#include <functional>
#include <thread>
#include <condition_variable>

namespace cpplab
{
    class ThreadPool
    {
        public:
        ThreadPool(size_t threads_count)
        {
            for (int i = 0; i < threads_count; ++i)
            {
                threads.emplace_back([]{
                    bool loop_condition = true;
                    while (loop_condition)
                    {
                        
                    }
                });
            }
        }

        ~ThreadPool()
        {
            stop();
        }

        void add_task(std::function<double()> task)
        {
            threads.emplace_back(task);
        }

        double average()
        {
            return 0;
        }

        void stop()
        {

        }

        private:
        std::vector<std::function<double()>> task_vector;
        std::vector<std::thread> threads;
        std::condition_variable cond_var;
        std::mutex mutex;
    };
}

int main()
{
    cpplab::ThreadPool basen {10};
    return 0;
}