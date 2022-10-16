#include <iostream>
#include <memory>
#include <initializer_list>
#include <string>

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
            this->_capacity = _capacity_base;
            this->_size++;
            this->array.reset(new T[this->_capacity]);
            this->array[0] = value;
        }

        Vector(std::initializer_list<T> values_list)
        {
            _size = values_list.size();
            _capacity = _size + (_size % _capacity_base) ? (_capacity_base - (_size % _capacity_base)) : 0;
            array.reset(new T[this->_capacity]);
            std::copy(values_list.begin(), values_list.end(), array.get());
        }

        void push_back(T value)
        {
            if (_size == _capacity)
            {
                this->resize(_capacity + _capacity_base);
            }
            array[_size] = value;
            _size++;
        }

        void pop(T index)
        {
            if(_size > 0)
            { 
                for (size_t i = index; i < this->_size-1; ++i)
                    array[i] = array[i+1];
                _size--;
            }
        }

        void pop_back()
        {
            if(_capacity > 0)
                _size--;
        }
        
        const size_t & size() const { return _size; }

        constexpr T &operator[](std::size_t id) const 
        { 
            if (id < _size)
                return this->array[id]; 
            else
                throw std::out_of_range("Tried to access element with index "+std::to_string(id)+" when size of the vector is "
                +std::to_string(_size)+".");
        }

        friend std::ostream& operator<<(std::ostream& os, const Vector& vec)
        {
            os << "{ ";
            for(int i = 0; i < vec._size; ++i)
                os << vec.array[i] << ", ";
            os << "\b\b }";
            return os;
        }

    private:
        size_t _capacity = 0;
        size_t _capacity_base = 4;
        size_t _size = 0;
        std::unique_ptr<T[]> array;

        void resize(size_t new_capacity)
        {
            T *new_array = new T[new_capacity];
            set_values(new_array);
            array_reset(new_array);
            this->_capacity = new_capacity;
        }

        void set_values(T *new_array)
        {
            for (size_t i = 0; i < this->_size; ++i)
                new_array[i] = array[i];
        }

        void array_reset(T *new_array)
        {
            array.reset(new_array);
            delete[] new_array;
        }
    
    };
}

    
    template<typename T1, typename T2>
    auto operator*(T1 const &lhs, T2 const &rhs) -> decltype(lhs[0]*rhs[0])
    {
        if(rhs.size() != lhs.size())
            throw std::logic_error("Both sizes must be equal in order to perform that operation");
        auto result = lhs[0]*rhs[0];
        for(int i = 1; i < lhs.size(); ++i)
            result += rhs[i]*lhs[i];
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
    std::cout << v2[0] << " "<< v2.size() <<"\n";
    std::cout << v2;

    cpplab::Vector<float> v3{2.4, 7.5, 21.6, 532.4};
    cpplab::Vector<float> v4{24.1, 5.3, 43.86, 32.97};
    std::cout<<std::endl<<v3<<std::endl;
    std::cout<<v3*v4<<"\n";
    v3.pop_back();
    std::cout<<v3<<"\n";
    v3.pop(1);
    std::cout<<v3<<"\n";
    cpplab::Vector<int> v5{24, 5, 4, 39};
    std::cout<<v4*v5<<"\n";
    std::cout<<v*v2;

    return 0;
}