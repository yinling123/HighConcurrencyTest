#include<iostream>
#include<mutex>
#include<thread>
#include<queue>
#include<condition_variable>
#include<vector>

std::queue<int> q;
std::condition_variable cv;
std::mutex mtx;

/**
 * 生产者线程，生产元素然后唤醒;不可以和消费者同时访问临界区
 */
void producer(){
    for(int i = 0; i < 10; i++){
        std::unique_lock<std::mutex> lck(mtx);
        q.push(i);
        std::cout << "producer: " << i << std::endl;
        cv.notify_one();
    }
}

/**
 * 消费者线程，队列中存在元素才可以去获取
 */
void consumer(){
    while(true){
        // 本身还是通过mutex进行阻塞
        std::unique_lock<std::mutex> lck(mtx);

        /**
         * 传入互斥量，如果函数返回false则一直阻塞，等待条件变量notify_one()被调用或者notif_all被调用唤醒变量
         * 只进行以此判断
         * wait如果返回false，则立刻释放锁，并且进行阻塞
         */ 
        cv.wait(lck,[]{return !q.empty();});

        std::cout << "consumer: " << q.front() << std::endl;

        q.pop();
    }
}

int main(){
    // 线程对象会在线程结束前自动销毁，并且自动调用析构函数来删除线程资源；并且线程对象的生命周期>=线程的生命周期
    std::thread t1(producer);
    std::vector<std::thread> t2;

    // emplace_back比push_back快，因为不需要创建临时变量
    for(int i = 0; i < 5; i++){
        t2.emplace_back(consumer);
    }
    

    t1.join();

    for(int i = 0; i < 5; i++){
       t2[i].join();
    }

    return 0;
}