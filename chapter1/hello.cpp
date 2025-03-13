#include <iostream>
#include <thread>
#include <string>

void hello(std::string msg)
{
    for (int i = 0; i < 10000; i++)
        std::cout << msg << std::endl;
}

void add(const int& a){
    std::cout << a << std::endl;
}

int main()
{
    // std::thread t(hello, "你好，曾倩");
    std::thread t1(add, 1);
    if (t1.joinable())
    {
        t1.join();
    }
    return 0;
}