#include<iostream>
#include<thread>
#include<atomic>

using namespace std;


atomic<int> a;

void func(){
    for(int i = 0; i < 10000000L; i++){
        a++;
    }
}

int main(){
    std::thread t1(func);

    t1.join();

    cout << a << endl;

    return 0;
}