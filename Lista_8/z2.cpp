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
        private:
        T* pointer;
    };
}

int main()
{
    
}