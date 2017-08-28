#include <iostream>

int main() {
    int a = 10;
    std::cout << "a = " << a << std::endl;
    auto f = [a]() -> int{return a;};
    auto f2 = [a]() mutable -> int{return ++a;};
    auto f3 = [](int x) -> int {
        if (x < 0)
            return -x;
        else
            return x;
    };
    a = 0;
    auto x = f();
    auto x2 = f2();
    auto x3 = f3(-1);
    std::cout << "a = " << a << std::endl;
    std::cout << "x = " << x << std::endl;
    std::cout << "x2 = " << x2 << std::endl;
    std::cout << "x3 = " << x3 << std::endl;
    return 0;
}
