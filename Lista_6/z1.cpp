#include <vector>
#include <future>
#include <iostream>
#include <numeric>

namespace cpplab
{
    void dot_product(std::vector<double> vec_1, std::vector<double> vec_2, std::promise<double> promise)
    {
        double sum = std::inner_product(vec_1.begin(), vec_1.end(), vec_2.begin(), 0);
        promise.set_value(sum);
    }
}

int main()
{
    std::vector<double> x{1, 3, 7}, y{2, 8, 9};
    std::promise<double> promise;
    std::future<double> future = promise.get_future();
    std::thread thread(cpplab::dot_product, x, y, std::move(promise));
    std::cout << "result=" << future.get() << '\n';
    thread.join();
}