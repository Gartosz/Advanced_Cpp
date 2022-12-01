#include <iostream>
#include <omp.h>


int main() 
{ 
    #pragma omp parallel
    #pragma omp critical
    std::cout << "Witaj z watku nr " << omp_get_thread_num() 
    << " sposrod " << omp_get_num_threads() << "\n"; 
}