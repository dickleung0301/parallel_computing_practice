#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> a{0};
void increment(){
    for(int i = 0; i < 10000; i++){
        a++;
    }
}

void increment_race(int& a){
    for(int i = 0; i < 10000; i++){
        a++;
    }
}

int main(){
    std::thread t_1(increment);
    std::thread t_2(increment);
    t_1.join();
    t_2.join();
    t_1.~thread();
    t_2.~thread();
    std::cout << "Value: " << a << std::endl;
    int i = 0;
    std::thread t_3(increment_race, std::ref(i));
    std::thread t_4(increment_race, std::ref(i));
    std::cout << "Race condition: " << i << std::endl;
    t_3.join();
    t_4.join();
    return 0;
}