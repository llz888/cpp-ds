#include <iostream>
using namespace std;

struct Base {
    Base()  { cout << "Base 构造里调 who()  -> "; who(); }
    virtual void who() { cout << "Base::who\n"; }
    virtual ~Base() { cout << "Base 析构里调 who()  -> "; who(); }
};

struct Derived : Base {
    Derived() { cout << "Derived 构造里调 who() -> "; who(); }
    void who() { cout << "Derived::who\n"; }
};

int main() {
    Derived d;
}