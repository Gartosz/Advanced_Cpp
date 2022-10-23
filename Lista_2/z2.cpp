#include <iostream>
#include <type_traits>

namespace cpplab
{
    template<typename T>
    class hypercube
    {
        public: 
        hypercube(T length, int dimensions)
        {
            if (dimensions < 2)
                throw std::logic_error(std::to_string(dimensions) + " is not a proper number of dimensions.");
            _edge_length = length;
            _dimensions = dimensions;
        }
        constexpr T calculate_volume()
        {
            T volume = 1;
            for (int i = 0; i < _dimensions; ++i)
                volume *= _edge_length;
            return volume;
        }
        private:
        T _edge_length;
        int _dimensions;
        
    };
}

int main()
{
    static_assert(cpplab::hypercube<double>::calculate_volume, "Nie uruchamia sie w trakcie kompilacji.");
    cpplab::hypercube cube_1(10, 3);
    std::cout << cube_1.calculate_volume() << "\n";
    
    cpplab::hypercube cube_2(14.86, 7);
    std::cout << cube_2.calculate_volume() << "\n";

    cpplab::hypercube cube_3(64, -4);
    std::cout << cube_3.calculate_volume() << "\n";

    return 0;
}