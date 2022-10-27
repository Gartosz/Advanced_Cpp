#include <iostream>
#include <string>

namespace cpplab
{
    template<typename T>
    class hypercube
    {
        public: 
        constexpr hypercube(T length, int dimensions)
        {
            _edge_length = length;
            _dimensions = dimensions;
        }
        constexpr T calculate_volume() const
        {
            if (_dimensions < 1)
                return -1;
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
    constexpr cpplab::hypercube cube_1(10, 3);
    std::cout << cube_1.calculate_volume() << "\n";
    
    static_assert(cube_1.calculate_volume() == 1000, "Nie uruchamia sie w trakcie kompilacji.");

    constexpr cpplab::hypercube cube_2(14.86, 7);
    std::cout << cube_2.calculate_volume() << "\n";

    constexpr cpplab::hypercube cube_3(64, -4);
    std::cout << cube_3.calculate_volume() << "\n";

    return 0;
}