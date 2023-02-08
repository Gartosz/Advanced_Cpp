namespace cpplab
{
    template <typename T>
    class unique_ptr
    {
        unique_ptr() : pointer(nullptr){} 
        private:
        T* pointer;
    };
}

int main()
{
    
}