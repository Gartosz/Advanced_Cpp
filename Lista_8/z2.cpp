#include <utility>
#include <iostream>

namespace cpplab
{
    template <typename Type>
    class unique_ptr
    {
        public:
        unique_ptr() : pointer(nullptr){} 
        unique_ptr(Type *ptr) : pointer(ptr) {}
        ~unique_ptr()
        {
            delete pointer;
        }
        Type* release()
        {
            return std::exchange(pointer, nullptr);
        }
        void reset(Type* ptr = nullptr) noexcept
        {
            delete pointer;
            pointer = ptr;
        }
        void swap( unique_ptr& other ) noexcept
        {
            std:swap(pointer, other.pointer);
        }
        private:
        Type* pointer;
    };
}

int main()
{
    
}