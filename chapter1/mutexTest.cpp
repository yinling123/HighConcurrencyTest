#include<iostream>
#include<mutex>
#include<thread>

std::mutex m;


void add(int& a){
    for(int i = 0; i < 10000; i++){
        std::lock_guard<std::mutex> lck(m);
        a++;
    }
}

int main(){

    int num = 0;

    std::thread t1(add, std::ref(num));
    std::thread t2(add, std::ref(num));

    if(t1.joinable()){
        t1.join();
    }

    if(t2.joinable()){
        t2.join();
    }
    
    std::cout << num << std::endl;

    return 0;
}