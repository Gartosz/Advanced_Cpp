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
            _capacity = 0;
            _size = 0;
        }

        Vector(T value)
        {
            _capacity = _capacity_base;
            _size = 1;
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

        Vector(const Vector &second_vector)
        {
            std::cout << "Copy constructor\n";
            copy_vector(second_vector);
        }

        Vector& operator=(const Vector& second_vector)
        {
            std::cout << "Copy assignment\n";
            copy_vector(second_vector);
            return *this;
        }

        Vector(Vector&& second_vector) noexcept
        {
            std::cout << "Move constructor\n";
            move_vector(second_vector);
        }

        Vector& operator=(Vector&& second_vector) noexcept
        {
            std::cout << "Move assignment\n";
            if (this != &second_vector)
            {
                array.release();
                move_vector(second_vector);
            }
            return *this;
        }

        ~Vector() { array.release(); }

        void push_back(T value)
        {
            if (_size == _capacity)
            {
                reallocate(_capacity + _capacity_base);
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
                reallocate(new_size);
                for(;_size < new_size;)
                    push_back(default_value);
            }
            else if(new_size < _size)
            {
                _size = new_size;
                reallocate(new_size);
            }
                
        }

        const size_t &size() const { return _size; }

        constexpr const T &operator[](std::size_t id) const
        {
            if (id < _size && id >= 0)
                return array[id];
            else
                throw std::out_of_range("Tried to access element with index " + std::to_string(id) + " when size of the vector is " + std::to_string(_size) + ".");
        }

        constexpr T &operator[](std::size_t id)
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
            if (vec._size != 0)
                os << "\b\b";
            os << " }";
            return os;
        }

    private:
        size_t _capacity;
        const size_t _capacity_base = 4;
        size_t _size;
        std::unique_ptr<T[]> array;

        void reallocate(size_t new_capacity)
        {
            _capacity = new_capacity + ((new_capacity % _capacity_base) ? (_capacity_base - (new_capacity % _capacity_base)) : 0);
            T *new_array = new T[_capacity];
            set_values<T*>(new_array, array);
            array.reset(new_array);
            _capacity = new_capacity;
        }

        template<typename A>
        void set_values(A &new_array, std::unique_ptr<T[]> const &old_array)
        {
            for (size_t i = 0; i < _size; ++i)
                new_array[i] = old_array[i];
        }

        void reduce_capacity()
        {
            if (_capacity > _capacity_base && _capacity - _capacity_base >= _size + 1)
                reallocate(_size);
        }

        inline bool check_size() { return _size > 0 ? true : false; }

        void copy_vector(const Vector &second_vector)
        {
            this->_capacity = second_vector._capacity;
            this->_size = second_vector._size;
            this->array = std::make_unique<T[]>(_capacity);
            set_values<std::unique_ptr<T[]>>(this->array, second_vector.array);
        }
        
        void move_vector(Vector& second_vector)
        {
            this->_capacity = second_vector._capacity;
            this->_size = second_vector._size;
            this->array = std::move(second_vector.array);

            second_vector._capacity = 0;
            second_vector._size = 0;
            second_vector.array.release();
        }
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
    
    cpplab::Vector<int> v2(v);

    v2[6] = 123;

    cpplab::Vector<int> v3 = v2;
    v3[1] = 9;
    std::cout << v << "\n" << v2 << "\n" << v3;

    return 0;
}