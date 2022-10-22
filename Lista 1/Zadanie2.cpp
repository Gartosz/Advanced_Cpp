#include <iostream>
#include <memory>
#include <initializer_list>
#include <string>
#include <vector>

namespace cpplab
{
    template <class T>
    class Vector
    {
    public:
        typedef T value_type;

        Vector()
        {
        }

        Vector(T value)
        {
            _capacity = _capacity_base;
            _size++;
            array.reset(new T[_capacity]);
            array[0] = value;
        }

        Vector(std::initializer_list<T> values_list)
        {
            _size = values_list.size();
            _capacity = _size + ((_size % _capacity_base) ? (_capacity_base - (_size % _capacity_base)) : 0);
            array.reset(new T[_capacity]);
            std::copy(values_list.begin(), values_list.end(), array.get());
        }

        void push_back(T value)
        {
            if (_size == _capacity)
            {
                change_capacity(_capacity + _capacity_base);
            }
            array[_size] = value;
            _size++;
        }

        void pop(T index)
        {
            if (check_size())
            {
                for (size_t i = index; i < _size - 1; ++i)
                    array[i] = array[i + 1];
                _size--;
                reduce_capacity();
            }
        }

        void pop_back()
        {
            if (check_size())
            {
                _size--;
                reduce_capacity();
            }
        }

        void resize(size_t new_size, T default_value)
        {
            if (new_size > _size)
            {
                change_capacity(new_size);
                for(;_size < new_size;)
                    push_back(default_value);
            }
            else if(new_size < _size)
            {
                _size = new_size;
                change_capacity(new_size);
            }
                
        }

        const size_t &size() const { return _size; }

        constexpr T &operator[](std::size_t id) const
        {
            if (id < _size && id >= 0)
                return array[id];
            else
                throw std::out_of_range("Tried to access element with index " + std::to_string(id) + " when size of the vector is " + std::to_string(_size) + ".");
        }

        friend std::ostream &operator<<(std::ostream &os, const Vector &vec)
        {
            os << "{ ";
            for (int i = 0; i < vec._size; ++i)
                os << vec.array[i] << ", ";
            os << "\b\b }";
            return os;
        }

    private:
        size_t _capacity = 0;
        const size_t _capacity_base = 4;
        size_t _size = 0;
        std::unique_ptr<T[]> array;

        void change_capacity(size_t new_capacity)
        {
            _capacity = new_capacity + ((new_capacity % _capacity_base) ? (_capacity_base - (new_capacity % _capacity_base)) : 0);
            T *new_array = new T[_capacity];
            set_values(new_array);
            array.reset(new_array);
            _capacity = new_capacity;
        }

        void set_values(T *new_array)
        {
            for (size_t i = 0; i < _size; ++i)
                new_array[i] = array[i];
        }

        void reduce_capacity()
        {
            if (_capacity > _capacity_base && _capacity - _capacity_base >= _size + 1)
                change_capacity(_size);
        }

        inline bool check_size() { return _size > 0 ? true : false; }
    };
}

template <typename T1, typename T2>
auto operator*(T1 const &lhs, T2 const &rhs) -> decltype(lhs[0] * rhs[0])
{
    if (rhs.size() != lhs.size())
        throw std::logic_error("Both sizes must be equal in order to perform that operation");
    auto result = lhs[0] * rhs[0];
    for (int i = 1; i < lhs.size(); ++i)
        result += rhs[i] * lhs[i];
    return result;
}

int main()
{
    cpplab::Vector<int> v;
    for (int i = 0; i < 10; ++i)
        v.push_back(i);

    std::cout << v << "\n";
    v[3] = 123;
    std::cout << v << "\n";

    cpplab::Vector<int> v2(856);
    std::cout << v2[0] << " " << v2.size() << "\n";
    std::cout << v2 << "\n";

    cpplab::Vector<float> v3{2.4, 7.5, 21.68, 532.4, 93.1};
    cpplab::Vector<double> v4{24.163, 5.3, 43.86, 32.97, 1.5};
    std::cout << v3 << v4 << std::endl;
    std::cout << v3 * v4 << "\n";
    v3.pop_back();
    std::cout << v3 << "\n";
    v3.pop(1);
    std::cout << v3 << "\n";
    cpplab::Vector<int> v5{24, 5, 4, 39, 17};
    std::cout << v4 * v5 << "\n";
    std::cout << v5 * v4 << "\n";

    cpplab::Vector<char> v_char{'a', 'c', 'g'};
    cpplab::Vector<std::string> v_string{"asd", "zxc", "qwe"};
    std::cout << v_char << v_string << "\n";
    std::cout << v_char * v_char << "\n";
    std::cout << v3 * v_char << "\n";
    std::vector<int> std_vector{1, 50, 83};
    std::cout << v3 * std_vector << "\n";
    v4.resize(10, 111.5);
    std::cout << v4 << "\n";
    v4.resize(6, 123.1);
    std::cout << v4;

    return 0;
}