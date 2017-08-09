#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>

bool ready = false;
bool processed = false;
std::string data;
std::mutex m;
std::condition_variable cv;

void worker_thread() {
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, []{return ready;});

    std::cout << "Start processing data..." << std::endl;
    data += " after process";

    processed = true;
    std::cout << "Worker thread signals data processing completed\n";

    // lk.unlock();
    cv.notify_one();
}

int main() {
    std::thread t(worker_thread);

    data = "Original data";
    {
        std::lock_guard<std::mutex> l(m);
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }
    cv.notify_one();

    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, []{return processed;});

    std::cout << "Back in main(), data = " << data << '\n';
    t.join();
    return 0;
}
