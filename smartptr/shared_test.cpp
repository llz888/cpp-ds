#include <iostream>
#include "mysharedptr.hpp"
using namespace std;

struct Foo {
    int x = 7;
    Foo()  { cout << ">> Foo 构造\n"; }
    ~Foo() { cout << ">> Foo 析构\n"; }
};

int main() {
    {
        MySharedPtr<Foo> a(new Foo());
        cout << "a.count() = " << a.count() << "\n";
        {
            MySharedPtr<Foo> b = a;              // 拷贝一份
            cout << "b.count() = " << b.count()
                 << "   a.count() = " << a.count() << "\n";
        }                                        // b 先走
        cout << "b 走了之后 a.count() = " << a.count() << "\n";
    }                                            // a 再走
    cout << "都走了\n";
    return 0;
}