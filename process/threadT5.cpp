#include<iostream>
#include<thread>
#include<mutex>

std::mutex mtx1;

std::mutex mtx2;

void func1(){
    mtx1.lock();
    mtx2.lock();
    mtx1.unlock();
    mtx2.unlock();
}

void func2(){
    mtx1.lock();
    mtx2.lock();
    mtx2.unlock();
    mtx1.unlock();
}

int main(){

    std::thread t1(func1);
    std::thread t2(func2);

    t1.join();
    t2.join();

    return 0;
}