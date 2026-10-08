#include <iostream>
  #include <string>
  using namespace std;

  struct Tracer {
      string name_;
      Tracer(const string& n) : name_(n) { cout << "构造 " << name_ << "\n";
  }
      ~Tracer() { cout << "析构 " << name_ << "\n"; }
  };

  int main() {
      Tracer* p = new Tracer("堆上的");
      Tracer& t = *p;                                    // 引用绑定到堆对象

      auto f = [&t]() { cout << "lambda 看到: " << t.name_ << "\n"; };
      //        ↑ 按引用捕获（你自己刚验证过：不拷贝）

      delete p;                                          // ← 对象死了
      cout << "--- 已 delete，现在调用 lambda ---\n";

      f();                                               // ← 会发生什么？

      return 0;
  }