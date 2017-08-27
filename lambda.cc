#include <iostream>

int main() {
    int a = 10;
    std::cout << "a = " << a << std::endl;
    auto f = [a]() -> int{return a;};
    a = 0;
    auto x = f();
    std::cout << "a = " << a << std::endl;
    std::cout << "x = " << x << std::endl;
    return 0;
}
