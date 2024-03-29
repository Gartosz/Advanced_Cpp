#include <vector>
#include <iostream>
#include <functional>
#include <thread>
#include <condition_variable>
#include <queue>

namespace cpplab
{
    class ThreadPool
    {
    public:
        ThreadPool(size_t threads_count)
        {
            sum = 0;
            done_tasks_count = 0;
            for (size_t i = 0; i < threads_count; ++i)
            {
                threads.emplace_back([this]{
                    do
                    {
                        std::function<double()> next_task;
                        {
                            std::unique_lock<std::mutex> lock(mutex);
                            this -> cond_var.wait(lock, [this] {return this -> stop_threads || !(this -> task_queue.empty());});
                            next_task = std::move(this -> task_queue.front());
                            this -> task_queue.pop();
                        }
                        if(next_task)
                        {
                            double result = next_task();
                            std::unique_lock<std::mutex> lock(mutex);
                            ++(this -> done_tasks_count);
                            this -> sum += result;
                        }

                        else if(this -> stop_threads)
                            this -> loop_condition = false;
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
            task_queue.emplace(std::move(task));
            cond_var.notify_one();
        }

        double average()
        {
            return done_tasks_count > 0 ? sum / done_tasks_count : 0;
        }

        void stop()
        {
            {
                std::unique_lock<std::mutex> lock(mutex);
                stop_threads = true;
            }
            cond_var.notify_all();
            for (auto &thread : threads)
                if (thread.joinable())
                    thread.join();
        }

    private:
        std::queue<std::function<double()>> task_queue;
        std::vector<std::thread> threads;
        std::condition_variable cond_var;
        std::mutex mutex;
        bool stop_threads = false;
        double sum;
        size_t done_tasks_count;
        bool loop_condition = true;
    };
}

int main()
{
    cpplab::ThreadPool basen{15};
    for (int i = 0; i < 1000; ++i)
        basen.add_task([i]{ return i * i; });
    basen.stop();
    std::cout << "Average: " << basen.average() << std::endl;
    return 0;
}