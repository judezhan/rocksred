#include <iostream>

class Shape {
    protected:
        int width, height;
    public:
        void set_value(int width, int height) {
            this->width = width;
            this->height = height;
        }
        virtual int area() = 0;
        void print_area() {
            std::cout << this->area() << std::endl;
        }
        ~Shape() {std::cout << "Shape deleted..." << std::endl;}
};

class Rectangle : public Shape {
    public:
        int area() {
            return this->width * this->height;
        }
        ~Rectangle() {std::cout << "Rectangle deleted..." << std::endl;}
};

class Triangle: public Shape {
    public:
        int area() {
            return this->width * this->height / 2;
        }
        ~Triangle() {std::cout << "Triangle deleted..." << std::endl;}
};


int main() {
    std::unique_ptr<Shape> sprec(new Rectangle());
    std::unique_ptr<Shape> sptri(new Triangle());
    sprec->set_value(4, 3);
    sptri->set_value(4, 3);
    sptri->print_area();
    sptri->print_area();
    // std::cout << rec.area() << std::endl;
    // std::cout << tri.area() << std::endl;
    return 0;
}
