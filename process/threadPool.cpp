#include<iostream>
#include<vector>
#include<queue>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<functional>


class ThreadPool{

public:

    ThreadPool(int n): stop(false){
        // 启动线程
        for(int i = 0; i < n; i++){
            workers.emplace_back([this](){
                while(true){
                    std::unique_lock<std::mutex> lock(mtx);
                    // 等待队列存入任务并且开始计算
                    cv.wait(lock, [this](){
                        return !tasks.empty() || stop;
                    });
                    
                    // 当任务执行的时候停止并且不存在任务时退出
                    if(stop && tasks.empty()){
                        return;
                    }

                    std::function<void()> task = std::move(tasks.front());
                    tasks.pop();
                    lock.unlock();
                    task();
                }
            });
        }
    }

    ~ThreadPool(){
        // 停止线程执行
        {
            std::unique_lock<std::mutex> lock(mtx);
            stop = true;
        }
        cv.notify_all();

        // 等待所有线程执行完毕，再销毁线程
        for(auto& worker: workers){
            worker.join();
        }
    }

    // 添加任务，函数入队列
    template<class F, class... Args>
    void enqueue(F&& f, Args&&... args){
        // 将绑定参数后的函数转化为void()类型
        std::function<void()> task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        {
            std::unique_lock<std::mutex> lock(mtx);
            tasks.emplace(task);
        }
        cv.notify_one();
    }


private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop;
};

int main(){

    ThreadPool pool(4);
    for(int i = 0; i < 10; i++){
        pool.enqueue([i](){
            std::cout << "task " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "task " << i << " done" << std::endl;
        });
    }

    return 0;
}