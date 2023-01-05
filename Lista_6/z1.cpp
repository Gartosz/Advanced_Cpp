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
    std::vector<int> x{1, 3, 7}, y{2, 8, 9};
    
}