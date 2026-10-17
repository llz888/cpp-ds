#include <iostream>
using namespace std;

struct Shape {
    virtual double area() const = 0;              // 纯虚
};

struct Circle : Shape {
    double r;
    Circle(double r_) : r(r_) {}
    double area() const { return 3.14159 * r * r; }   // 实现了
};

int main() {
 
    Circle c(1.0);
    Shape* p = &c;
    cout << p->area() << "\n";
}