#include <iostream>
#include <thread>
#include <vector>

std::once_flag flag;

void task() {
    std::call_once(flag, []() {std::cout << "Call once" << std::endl;});
    std::cout << "Lalala" << std::endl;
}

int main() {
    std::vector<std::thread> threads;
    for (int i=0; i<5; i++) {
        threads.push_back(std::thread(task));
    }

    for (auto& t: threads) {
        t.join();
    }

    return 0;
}
