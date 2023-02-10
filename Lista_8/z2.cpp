namespace cpplab
{
    template <typename T>
    class unique_ptr
    {
        unique_ptr() : pointer(nullptr){} 

        ~unique_ptr()
        {
            delete pointer;
        }
        T release()
        {
            return std::exchange(pointer, nullptr);
        }
        void reset(T* ptr = nullptr) noexcept
        {
            delete pointer;
            pointer = ptr;
        }
        private:
        T* pointer;
    };
}

int main()
{
    
}