#include <iostream>

namespace cpplab
{
    template<typename T, T _edge_length, int _dimensions>
    class hypercube
    {
        public: 
        static constexpr T calculate_volume()
        {
            if (_dimensions < 0)
                return -1;
            T volume = _dimensions == 0 ? 0 : 1;
            for (int i = 0; i < _dimensions; ++i)
                volume *= _edge_length;
            return volume;
        }
    };
}

int main()
{
    std::cout << cpplab::hypercube<int, 10, 3>::calculate_volume() << "\n";
    
    static_assert(cpplab::hypercube<int, 10, 3>::calculate_volume() == 1000, "Nie uruchamia sie w trakcie kompilacji.");

    std::cout << cpplab::hypercube<double, 14.86, 7>::calculate_volume() << "\n";

    std::cout << cpplab::hypercube<int, 4, 0>::calculate_volume() << "\n";

    std::cout << cpplab::hypercube<float, 64.9f, -4>::calculate_volume() << "\n";

    return 0;
}