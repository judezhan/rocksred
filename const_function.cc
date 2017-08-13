#include <iostream>

class A {
    private:
        int value;
        A(const A& a);
    public:
        A(int value_) : value(value_) {};
        int get_value() const {return value;};
};

void func(const A& a) {
    std::cout << a.get_value() << std::endl;
}

void func2(const A& a) {
    std::cout << a.get_value() << std::endl;
}

int main() {
    A a1(3);
    const A a2(4);
    func(a1);
    func2(a2);
}
