#include <iostream>

class A {
    private:
        int value;
    public:
        A(int value) : value(value) {};
        ~A() {
            std::cout << "Delete A..." << std::endl;
        }
        void setValue(int value) {
            this->value = value;
        }
        void printValue() {
            std::cout << "Current value is " << this->value << std::endl;
        }
};

int main() {
    // std::unique_ptr<A> aPtr(new A(1));
    // std::unique_ptr<A> aPtr2;
    // // aPtr2 = aPtr;
    // aPtr2 = std::move(aPtr);
    // // aPtr->printValue();
    // aPtr2->printValue();

    std::shared_ptr<A> sPtr(new A(2));
    std::shared_ptr<A> sPtr2;
    sPtr2 = sPtr;
    sPtr->printValue();
    sPtr->printValue();
    return 0;
}
