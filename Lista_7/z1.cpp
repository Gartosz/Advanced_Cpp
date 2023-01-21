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
                threads.emplace_back([this]{
                    bool loop_condition = true;
                    do
                    {
                        std::unique_lock<std::mutex> lock(mutex);
                        this -> cond_var.wait(lock, [this] {return this -> stop_threads;});

                        if(this -> stop_threads)
                            loop_condition = false;
                    }while (loop_condition);
                });
            }
        }

        ~ThreadPool()
        {
            stop();
        }

        void add_task(std::function<double()> task)
        {
            std::unique_lock<std::mutex> lock(mutex);
            threads.emplace_back(std::move(task));
            cond_var.notify_one();
        }

        double average()
        {
            return 0;
        }

        void stop()
        {
            {
                std::unique_lock<std::mutex> lock(mutex);
                stop_threads = true;
            }
            cond_var.notify_all();
            for (auto &thread : threads)
                thread.join();

        }

        private:
        std::vector<std::function<double()>> task_vector;
        std::vector<std::thread> threads;
        std::condition_variable cond_var;
        std::mutex mutex;
        bool stop_threads = false;
    };
}

int main()
{
    cpplab::ThreadPool basen {10};
    basen.stop();
    return 0;
}