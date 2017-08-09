#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>

void task(std::string name) {
    std::__thread_id tid = std::this_thread::get_id();
    for (int i=0; i<10; i++) {
        std::cout << "[" << tid << "] Hello " << name << i << std::endl;
        // std::cout << "Hello " << name << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void hello() {
    std::cout << "Hello from " << std::this_thread::get_id() << std::endl;
}

int main() {
    // std::thread t1(task, "jude");
    // std::thread t2(task, "sherry");
    // std::this_thread::sleep_for(std::chrono::seconds(2));
    // std::cout << "Hahaha" << std::endl;
    // // t1.join();
    // t2.join();
    std::vector<std::thread> threads;
    for (int i=0; i < 10; i++) {
        threads.push_back(std::thread(hello));
    }
    for (auto& t : threads) {
        t.join();
    }
    return 0;
}
