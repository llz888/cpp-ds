#include <iostream>
using namespace std;

struct Base {
    virtual ~Base() { cout << "~Base\n"; }          // ← 注意：没有 virtual
};

struct Derived : Base {
    int* buf = new int[100];                 // 派生类自己有一块资源
    ~Derived() { delete[] buf; cout << "~Derived\n"; }
};

int main() {
    Base* p = new Derived;
    delete p;                                // ← 通过基类指针删除
}