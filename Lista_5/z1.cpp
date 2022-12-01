#include <iostream>
#include <string>

namespace cpplab
{
    int get_id()
    {
        thread_local int thread_id = -1;
        return thread_id;
    }
    void print(std::string const &text)
    {
        std::cout << get_id() << " " << text << "\n";
    }
}

int main()
{

}