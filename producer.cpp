#include "iostream"
#include <thread>
#include <chrono>


int main() 
{
    while (true)
    {
        std::cout << "Hello World!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
    
    return 0;
}