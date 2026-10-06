#include <iostream>
#include <utility>
#include "myuniqueptr.hpp"

using namespace std;

struct Foo {
    int x = 0;
    Foo()  { cout << ">> Foo 构造\n"; }
    ~Foo() { cout << ">> Foo 析构\n"; }
};

int main() {
    cout << "---- 接管一个裸指针 ----\n";
    MyUniquePtr<Foo> p(new Foo());
    p->x = 1;
    (*p).x = 2;
    cout << "p->x = " << p->x << "\n";

    cout << "---- 搬走给 q ----\n";
    MyUniquePtr<Foo> q = std::move(p);
    cout << "q.get() = " << q.get() << "    p.get() = " << p.get() << "\n";
    cout << "q->x = " << q->x << "\n";

    cout << "---- 结束，q 出作用域 ----\n";
    MyUniquePtr<Foo> r(new Foo());
    r = std::move(q);        // ← 第一次真正调用移动赋值
    return 0;
}

// 验收 2：下面这行必须编译不过。
// 取消注释试一次，看到报错后再注释回去。
//
// MyUniquePtr<Foo> r = p;
