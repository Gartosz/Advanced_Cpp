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
        }
    }
    }

int main()
{
}