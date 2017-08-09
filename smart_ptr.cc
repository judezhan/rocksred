#include <iostream>

class B;
class A {
    public:
        // std::shared_ptr<B> pb_;
        std::weak_ptr<B> pb_;
        std::string str;

        A(std::string s) {
            this->str = s;
        }
        ~A() {
            std::cout << "Delete A with str=" << this->str << "..." << std::endl;
        }
        void print() {
            std::cout << this->str << std::endl;
        }
};

class B {
    public:
        std::shared_ptr<A> pa_;
        std::string str;

        B(std::string s) {
            this->str = s;
        }
        ~B() {
            std::cout << "Delete B with str=" << this->str << "..." << std::endl;
        }
        void print() {
            std::cout << this->str << std::endl;
        }
};

void func() {
    std::shared_ptr<A> pa(new A("a"));
    std::shared_ptr<B> pb(new B("b"));
    pa->pb_ = pb;
    pb->pa_ = pa;
    std::cout << pb.use_count() << std::endl;
    std::cout << pa.use_count() << std::endl;
}


int main() {
    // std::shared_ptr<A> pa(new A("test"));
    // pa->print();
    // pa.reset(new A("test2"));
    // pa->print();
    func();
    return 0;
}
