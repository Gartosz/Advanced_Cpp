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
        Type *get() const noexcept {return pointer;}
        Type &operator*() const noexcept {return *pointer;}
        Type *operator->() const noexcept {return pointer;}
        explicit operator bool() const noexcept {return static_cast<bool>(pointer);}
        private:
        Type* pointer;
    };

}

int main()
{
    cpplab::unique_ptr<int> u_ptr(new int(5));
    std::cout << *u_ptr << "\n";
    *u_ptr = 8;
    std::cout << *u_ptr << "\n";
    u_ptr.reset(new int(123));
    std::cout << *u_ptr << "\n";
    cpplab::unique_ptr<int> u_ptr2(new int(76));
    std::cout << *u_ptr2 << "\n";
    u_ptr.swap(u_ptr2);
    std::cout << *u_ptr << " " << *u_ptr2 << "\n";
    cpplab::unique_ptr<cpplab::test> asd(new cpplab::test(15));
    std::cout << asd->member << "\n";
    u_ptr.release();
    std::cout << "Points to " << (u_ptr ? "address." : "nullptr.");
}