#include <iostream>

template <class Type> class Queue {
    public:
        Type &front() {};
        void push(Type item) {
            std::cout << item << " been pushed" << std::endl;
        }
};

int main() {
    Queue<int> int_queue;
    int_queue.push(1);

    Queue<std::string> string_queue;
    string_queue.push("abc");

    return 0;
}
