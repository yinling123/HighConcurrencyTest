#include<iostream>
#include<thread>

void foo(int& a){
    a++;
}

int main(){
    int a = 1;
    foo(a);
    /*
     通过函数强制转化为引用，延迟变量生命周期，必须采用引用方式，因为线程内部默认值传递，不会转化为引用
    */ 
    std::thread t1(foo, std::ref(a));

    if(t1.joinable()){
        t1.join();
    }
    
    std::cout << "a = " << a << std::endl;

    return 0;
}