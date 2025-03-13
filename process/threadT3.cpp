#include<iostream>
#include<thread>
#include<memory>

class MyClass {
private:
    // 外部线程调用私有成员函数，只可以通过友元
    friend void thread_foo();
    void func1(){
        std::cout<<"func1"<<std::endl;
    }
        
};

void thread_foo(){
    // 注意线程运行时，类变量不可提前释放，不然发生错误，可采用智能指针简化此类问题
    MyClass* obj = new MyClass;
    std::shared_ptr<MyClass> ptr(obj);

    std::thread t1(&MyClass::func1, ptr);

    t1.join();
}

int main(){

    int&& a = 42;
    a = 432;
    std::cout << a << std::endl;
    thread_foo();
    return 0;
}