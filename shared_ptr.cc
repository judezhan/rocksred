#include <iostream>
#include <memory>

class A : public std::enable_shared_from_this <A>{
    public:
        A() : value(0) {}
        ~A() { std::cout << "A ~A() called" << std::endl;}
        std::shared_ptr<A> get_object() {
            return shared_from_this();
        }
        void print_value() { std::cout << value << std::endl;}
    private:
        int value;
};

class B : public std::enable_shared_from_this<B> {
    public:
        B() {
            spb = shared_from_this();
        }
    private:
        std::shared_ptr<B> spb;
};

int main() {
    std::shared_ptr<A> spa(new A());
    std::shared_ptr<B> spb(new B());
    std::cout << spa.use_count() << std::endl;
    std::cout << spb.use_count() << std::endl;
}
