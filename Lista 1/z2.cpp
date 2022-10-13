#include <iostream>
#include <memory>
#include <initializer_list>

namespace cpplab
{
    template <class T>
    class Vector
    {
    public:
        typedef T value_type;
        size_t size = 0;
        Vector()
        {
        }

        Vector(T value)
        {
            this->capacity = 2;
            this->size++;
            this->array.reset(new T[this->capacity]);
            this->array[0] = value;
        }

        Vector(std::initializer_list<T> values_list)
        {
            size = values_list.size();
            capacity = size % 2 ? size + 1 : size;
            array.reset(new T[this->capacity]);
            std::copy(values_list.begin(), values_list.end(), array.get());
        }

        void push_back(T value)
        {
            if (size == capacity)
            {
                this->resize(capacity + 2);
            }
            array[size] = value;
            size++;
        }

        void pop(T index)
        {
            if(size > 0)
            { 
                for (size_t i = index; i < this->size-1; ++i)
                    array[i] = array[i+1];
                size--;
            }
        }

        void pop_back()
        {
            if(capacity > 0)
                size--;
        }

        T &operator[](std::size_t id) const { return this->array[id]; }
        T &operator[](std::size_t id) { return this->array[id]; }

        friend std::ostream& operator<<(std::ostream& os, const Vector& vec)
        {
            os << "{ ";
            for(int i = 0; i < vec.size; ++i)
                os << vec.array[i] << ", ";
            os << "\b\b }";
            return os;
        }

    private:
        size_t capacity = 0;
        std::unique_ptr<T[]> array;

        void resize(size_t new_capacity)
        {
            T *new_array = new T[new_capacity];
            set_values(new_array);
            array_reset(new_array);
            this->capacity = new_capacity;
        }

        void set_values(T *new_array)
        {
            for (size_t i = 0; i < this->size; ++i)
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
    auto operator*(T1 const &lhs, T2 const &rhs) 
    {
        if(rhs.size != lhs.size)
            throw std::logic_error("Both sizes must be equal in order to perform that operation");
        auto result = 0;
        for(int i = 0; i < lhs.size; ++i)
            result += rhs[i]*lhs[i];
        return result;
    }


int main()
{
    cpplab::Vector<int> v;

    for (int i = 0; i < 10; ++i)
        v.push_back(i);

    v[3] = 123;

    std::cout << v << "\n";

    cpplab::Vector<int> v2(856);
    std::cout << v2[0] << "\n";
    std::cout << v2;

    cpplab::Vector<float> v3{2.4, 7.5, 21.6, 532.4};
    cpplab::Vector<float> v4{24.1, 5.3, 43.86, 32.94};
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