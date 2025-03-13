#include<iostream>
#include<thread>
#include<mutex>
#include<string>

static std::once_flag flag;

class Log{
public:

    static Log* log;

    Log(){}

    Log(const Log&) = delete;
    
    Log& operator=(const Log&) = delete;

    /**
     * 单例模式
     * 通过采用 std::call_once 来保证线程安全，一个函数同时只可以被一个线程访问
     * call_once 函数，第一个参数为 std::once_flag 对象，第二个参数为函数指针，第三个参数为函数参数
     * call_once 只可以在线程函数中使用，main函数中不可以调用包含call_once的函数
     */
    static Log& getInstance(){

        std::call_once(flag, &Log::init);
        return *log;
    }

    static void writeLog(){
        std::cout << "write log" << std::endl;
    }

    static void init(){
        if(!log){
            log = new Log();
        }
    }
};

Log* Log::log = nullptr;

void test(){
    Log::getInstance().writeLog();
}


int main(){

    std::thread t1(test);
    std::thread t2(test);

    t1.join();
    t2.join();

    return 0;
}