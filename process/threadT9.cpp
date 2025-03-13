#include<iostream>
#include<thread>
#include<future>

int func(){
    int i = 0;
    for(int j = 0; j < 10000; j++){
        i++;
    }
    return i;
}

void fun(std::promise<int>& p){
    for(int i = 0; i < (long long)100000; i++){

    }
    p.set_value(19999);
}

int main(){

    // 直接异步执行线程
    std::future<int> f = std::async(func);
    // 当调用get的时候，主线程会阻塞，等待子线程执行完成
    // std::cout << f.get() << std::endl;

    // 封装函数
    std::packaged_task<int()> pt(func);
    // 获取函数的返回值，提前获取位置
    std::future<int> f2 = pt.get_future();

    // 采用拷贝构造，将pt移动到线程t中，packaged_task只能被移动，不能被拷贝
    std::thread t(std::move(pt));

    t.join();

    std::cout << f2.get() << std::endl;

    // 创建一个空间
    std::promise<int> f3;

    std::thread t1(fun, std::ref(f3));

    // t1.join();

    std:: cout << f3.get_future().get() << std::endl;

    t1.join();
    return 0;
}