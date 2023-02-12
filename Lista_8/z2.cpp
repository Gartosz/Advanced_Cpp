#include <utility>
#include <iostream>

namespace cpplab
{
    class test
    {
        public:
        test(int int_) {member = int_;}
        int member = 0;
    };

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
        void swap( unique_ptr &other ) noexcept
        {
            std::swap(pointer, other.pointer);
        }
        Type get() const noexcept {return pointer;}
        Type operator*() const noexcept {return *pointer;}
        Type *operator->() const noexcept {return pointer;}
        private:
        Type* pointer;
    };

}

int main()
{
    cpplab::unique_ptr<int> c(new int(10));
    std::cout << *c << "\n";
    c.release();
    cpplab::unique_ptr<cpplab::test> asd(new cpplab::test(15));
    std::cout << asd->member << "\n";
}