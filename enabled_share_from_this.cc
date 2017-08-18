#include <iostream>

class A : public std::enable_shared_from_this <A> {
    public:
        std::shared_ptr<A> get_sptr_a() {
            return A::shared_from_this();
        }
        ~A() {std::cout << "A ~A called" << std::endl;}
};

int main() {
    std::shared_ptr<A> sptr_a(new A());
    std::shared_ptr<A> sptr_b = sptr_a->get_sptr_a();
}
