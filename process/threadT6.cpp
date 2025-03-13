#include<iostream>
#include<thread>
#include<mutex>

int shared_data = 0;

// 线程等待的时候直接进入休眠状态
std::mutex mtx;
std::timed_mutex mtx1;

void func(){
    for(int i = 0; i < 100000; i++){
        // 只可以局部使用
        std::lock_guard<std::mutex> lock(mtx);
        shared_data++;
    }
}

void func2(){
    for(int i = 0; i < 100000; i++){
        /**
         * 更加灵活，两者本质都是对于同一个互斥量进行管理，因此同时只可以一个线程进入临界区
         * defer_lock：不进行锁定，需要手动调用lock()进行锁定 
         * try_lock_for：尝试锁定，如果锁定失败，则等待一段时间，如果锁定成功，则继续执行
         */ 
        std::unique_lock<std::timed_mutex> lock(mtx1, std::defer_lock); 
        lock.try_lock_for(std::chrono::seconds(1));
        shared_data++;
        lock.unlock();
    }
}

int main(){
    std::thread t1(func2);
    std::thread t2(func2);

    t1.join();
    t2.join();

    std::cout << "shared_data = " << shared_data << std::endl;

    return 0;
}