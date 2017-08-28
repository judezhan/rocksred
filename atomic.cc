#include <iostream>
#include <thread>
#include <vector>

class A {
    private:
        // std::atomic<int> value;
        std::atomic_int value;
        // int value;

    public:
        A() : value(0) {}

        void increase() {
            ++value;
        }

        void decrease() {
            --value;
        }

        void print() {
            std::cout << value << std::endl;
        }
};

class B {
    private:
        std::mutex mutex;
        int value;

    public:
        B() : value(0) {}

        void increase() {
            std::lock_guard<std::mutex> lock(mutex);
            ++value;
        }

        void decrease() {
            --value;
        }

        void print() {
            std::cout << value << std::endl;
        }
};



int main() {
    A b;
    std::vector<std::thread> threads;
    for (int i=0; i<100; ++i) {
        threads.push_back(std::thread([&b]() {
            for (int j=0; j<10000; ++j) {
                b.increase();
            }
        }));
    }

    for (auto& t: threads) {
        t.join();
    }
    b.print();
    return 0;
}
