#include <mutex>
#include <iostream>
#include <thread>

std::mutex m;
int a = 0;

void foo(){
    m.lock(); // when a thread own mutex, all other threads will block
    a++;
    std::cout << a << std::endl;
    m.unlock();
}

void foo_2(){
    std::lock_guard<std::mutex> guard(m);
    /*
    create a lock guard and acquire the mutex
    no need to explicitly unlock the mutex, it will be unlocked when guard goes out of scope
    */
}

int main(){
    std::thread t1(foo);
    std::thread t2(foo);
    t1.join();
    t2.join();
    return 0;
}
