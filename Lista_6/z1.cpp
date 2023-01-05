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
    std::vector<std::promise<double>> promises(10);
    std::vector<std::future<double>> futures;
    std::vector<std::thread> threads;
    double dot = 0;
    for (int i = 0; i < promises.size(); ++i)
    {
        futures.push_back(promises[i].get_future());
        threads.push_back(std::thread(cpplab::dot_product, x, y, std::move(promises[i])));
        dot += futures[i].get();
        threads[i].join();
    }
    std::cout << "Wynik: " << dot;
}