#include <iostream>
#include <string>
using namespace std;

struct Tracer {
    string name_;
    Tracer(const string& n) : name_(n) { cout << "构造 " << name_ << "\n"; }
    Tracer(const Tracer& o) : name_(o.name_) { cout << "拷贝构造 " << name_ << "\n"; }
    ~Tracer() { cout << "析构 " << name_ << "\n"; }
};

int main() {
    Tracer* p = new Tracer("堆上的");
    Tracer& t = *p;

    auto f = [t]() { cout << "lambda 看到: " << t.name_ << "\n"; };
    // ↑ 只把 & 去掉了

    delete p;   // ← 原对象死了

    cout << "--- 已 delete，现在调用 lambda ---\n";
    f();        // ← 会发生什么？

    return 0;
}