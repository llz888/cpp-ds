 #include <iostream>
  #include <string>
  using namespace std;

  struct Tracer {
      string name_;
      Tracer(const string& n) : name_(n) { cout << "构造 " << name_ << "\n";
  }
      Tracer(const Tracer& o) : name_(o.name_) { cout << "拷贝构造 " <<
  name_ << "\n"; }
      ~Tracer() { cout << "析构 " << name_ << "\n"; }
  };

  int main() {
      Tracer t("A");

      cout << "--- 1. 创建 lambda ---\n";
      auto f = [t]() { cout << "lambda 里看到: " << t.name_ << "\n"; };

      cout << "--- 2. 调用 lambda 两次 ---\n";
      f();
      f();

      cout << "--- 3. 结束 ---\n";
      return 0;
  }