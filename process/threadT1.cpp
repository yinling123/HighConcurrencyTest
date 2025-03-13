#include<thread>
#include<iostream>

int i = 10;

void helloWord(){
    std::cout << "hello world" <<  ++i << std::endl; 
}

void helloworld(std::string str){
    while(true){

    }
    std::cout << "hello world" << str << std::endl;
}

int main(){
    // 创建线程，线程对象负责管理线程，所以不允许在执行完成前销毁，除非采用 join 或者 detach
    std::thread t1(helloWord);

    // 采用string 的拷贝构造函数生成
    std::thread t2(helloworld, "thread2");

    // 判断线程是否可以被join或者detach
    if(t1.joinable()){
        // 阻塞主线程退出等在子进程完成才可退出
        t1.join();
    }

    // 分离线程，子线程执行时，主线程继续运行；后台运行子线程
    t2.detach();

    return 0;
}