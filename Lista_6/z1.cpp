#include <vector>
#include <future>
#include <iostream>
#include <numeric>
#include <cassert>

namespace cpplab
{
    void dot_product(std::vector<double> vec_1, std::vector<double> vec_2, std::promise<double> promise)
    {
        try 
        {
            if (vec_1.size() != vec_2.size())
                throw std::logic_error("Both vectors must have the same size!");
            if (vec_1.size() == 0 || vec_2.size() == 0)
                throw std::logic_error("Each vector cannot be empty!");

            double sum = std::inner_product(vec_1.begin(), vec_1.end(), vec_2.begin(), 0);
            promise.set_value(sum);
        }
        catch (std::exception)
        {
            promise.set_exception(std::current_exception());
        }
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
    std::cout << "Wynik: " << dot << std::endl;

    std::vector<double> a{1, 3, 7, 123}, b{2, 8, 9};
    std::promise<double> promise;
    std::future<double> future = promise.get_future();
    std::thread thread_exception_1(cpplab::dot_product, a, b, std::move(promise));

    std::cout << future.get();
    thread_exception_1.join();

    std::thread thread_exception_2(cpplab::dot_product, std::vector<double> (), std::vector<double> (), std::move(promise));

    std::cout << future.get();
    thread_exception_2.join();
}