#include <iostream>
#include <thread>

void hello(){
    std::cout << "Hello from thread " << std::this_thread::get_id() << "\n";
}

int main(){
    std::thread t1(hello); // create and start a new thread
    std::thread t2(hello); // create another new thread
    t1.join(); // returns when the thread execution is completed, sychronise the moment this function returns
    t2.join(); // race condition
    std::cout << "Hello from main thread " << std::this_thread::get_id() << "\n";
}