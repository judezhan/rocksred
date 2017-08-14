#include <iostream>

void f1(int a, int b, int c) {
    std::cout << a + b + c << std::endl;
}

int main() {
    auto bf1 = std::bind(f1, 1, 2, 3);
    auto bf2 = std::bind(f1, 1, 2, std::placeholders::_1);
    auto bf3 = std::bind(f1, 1, std::placeholders::_1, std::placeholders::_1);
    bf1();
    bf2(4);
    bf3(5, 6);
    return 0;
}
