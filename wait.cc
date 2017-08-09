#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>

std::mutex m;
std::condition_variable cv;
int i = 0;

void waits() {
    std::unique_lock<std::mutex> ulk(m);
    std::cout << std::this_thread::get_id() << " Waiting..." << std::endl;
    cv.wait(ulk, []{return i==1;});
    std::cout << std::this_thread::get_id() << " Finish waiting with i=" << i << std::endl;
}

void signals() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> mlk(m);
        std::cout << "Notify All..." << std::endl;
    }
    cv.notify_all();

    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> mlk(m);
        i = 1;
        std::cout << "Notify All Again..." << std::endl;
    }
    cv.notify_all();
}

int main() {
    std::thread t1(waits), t2(waits), t3(waits), t4(signals);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}
