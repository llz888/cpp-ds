#include <iostream>
#include <string>
using namespace std;

struct Tracer {
    string name_;
    Tracer(const string& n) : name_(n) { cout << "构造 " << name_ << "\n"; }
    ~Tracer() { cout << "析构 " << name_ << "\n"; }
};

auto make() {
    Tracer t("栈上的");
    return [&t]() { cout << "lambda 看到: " << t.name_ << "\n"; };
}

int main() {
    auto g = make();
    cout << "--- make() 已经返回 ---\n";
    g();
    return 0;
}