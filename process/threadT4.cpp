#include<iostream>
#include<mutex>
#include<thread>

int a = 0;

std::mutex mtx;

void foo(){
    for(int i = 0; i < 1000000; i++)
    {
        // 通过互斥锁进行处理，避免线程安全问题
        mtx.lock();
        a++;
        mtx.unlock();
    }
} 

int main(){

    std::thread t1(foo);


    std::thread t2(foo);

    t1.join();
    t2.join();

    std::cout << a << std::endl;

    return 0;
}