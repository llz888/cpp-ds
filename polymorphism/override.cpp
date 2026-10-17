#include <iostream>
using namespace std;

struct Base {
    virtual void who() const { cout << "Base\n"; }
};

struct Derived : Base {
    void who() const override { cout << "Derived\n"; }     // ← 注意：少了 const
};

int main() {
    Derived d;
    Base* p = &d;
    p->who();
}