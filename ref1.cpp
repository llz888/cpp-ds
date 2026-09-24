#include <iostream>
  #include <string>
  using namespace std;

  struct Tracer {
      string name_;
      Tracer(const string& n) : name_(n) {}
  };

  int main() {
      Tracer a("A");
      Tracer b("B");

      Tracer* p = &a;
      Tracer& r = a;

      cout << "初始:   a=" << a.name_ << "   b=" << b.name_ << "\n";

      p = &b;                 // 指针：改指向
      r = b;                  // 引用：这是在"改绑"吗？

      cout << "之后:   a=" << a.name_ << "   b=" << b.name_ << "\n";
      cout << "p 指向: " << p->name_ << "\n";
      cout << "r 看着: " << r.name_ << "\n";

      return 0;
  }