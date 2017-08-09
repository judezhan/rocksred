#include <iostream>

class Line {
    public:
        static int count;
        int getLength();
        Line(int);
        Line(const Line& obj);
        ~Line();
        static int getCount() {
            return count;
        };

    private:
        int* ptr;
};

int Line::count = 0;

Line::Line(int length) {
    std::cout << "调用构造函数..." << std::endl;
    ptr = new int;
    *ptr = length;
    count++;
}

Line::Line(const Line &obj) {
    std::cout << "调用深拷贝构造函数..." << std::endl;
    ptr = new int;
    *ptr = *obj.ptr;
    count++;
}

int Line::getLength() {
    std::cout << "Call getLength func..." << std::endl;
    return *ptr;
}

Line::~Line() {
    std::cout << "释放内存..." << std::endl;
    delete ptr;
}

void displayLine(Line line) {
    std::cout << "Display Line: " << line.getLength() << std::endl;
}

int main() {
    std::cout << "Init..." << std::endl;
    Line line1(10);

    std::cout << "Going to init line2" << std::endl;
    Line line2 = line1;

    // std::cout << "Going to display line1" << std::endl;
    // displayLine(line1);

    // std::cout << "Going to display line2" << std::endl;
    // displayLine(line2);

    // std::cout << "Finish display lines" << std::endl;

    Line* linePtr;
    linePtr = &line1;
    std::cout << linePtr->getLength() << std::endl;

    std::cout << Line::getCount() << std::endl;

    return 0;
}
