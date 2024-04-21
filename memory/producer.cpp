#include "iostream"
#include <thread>
#include <chrono>


int main() 
{
    int a = 10000;
    std::cout << &a << std::endl;
    while (true)
    {
        std::cout << "Input a new value: ";
        std::cin >> a;
    }
    return 0;
}