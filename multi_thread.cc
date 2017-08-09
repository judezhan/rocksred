#include <iostream>
#include <thread>
#include <vector>

class Counter {
    private:
        std::mutex mutex;
        int value;
    public:
        Counter(): value(0) {};
        void increaseValue() {
            std::lock_guard<std::mutex>lock(mutex);
            value++;
        }
        void printValue() {
            std::cout << this->value << std::endl;
        }
};

struct Complex {
    int value;
    // std::recursive_mutex mutex;
    std::mutex mutex;

    Complex() : value(10) {}

    void mul(int i) {
        // std::lock_guard<std::recursive_mutex> lock(mutex);
        std::lock_guard<std::mutex> lock(mutex);
        value *= i;
    }

    void div(int i) {
        // std::lock_guard<std::recursive_mutex> lock(mutex);
        std::lock_guard<std::mutex> lock(mutex);
        value /= i;
    }

    void both(int i) {
        // std::lock_guard<std::recursive_mutex> lock(mutex);
        std::lock_guard<std::mutex> lock(mutex);
        mul(i);
        div(i);
    }

    void printValue() {
        std::cout << value << std::endl;
    }
};

void task(Counter& c) {
    for (int i=0; i<10000; i++) {
        c.increaseValue();
    }
}

int main() {
    // Counter c;
    Complex _complex;
    std::vector<std::thread> threads;
    for (int i=0; i<100; i++) {
        threads.push_back(std::thread([&_complex]() {
            for (int i=0; i<10; i++) {
                _complex.both(10);
            }
        }));
        // threads.push_back(std::thread(task, std::ref(c)));
    }

    for (auto& t : threads) {
        t.join();
    }

    _complex.printValue();
    return 0;
}
