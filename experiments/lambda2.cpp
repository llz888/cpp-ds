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

      cout << "--- 1. 按值捕获 [t] ---\n";
      auto f1 = [t]()  { cout << "f1: " << t.name_ << "\n"; };

      cout << "--- 2. 按引用捕获 [&t] ---\n";
      auto f2 = [&t]() { cout << "f2: " << t.name_ << "\n"; };

      cout << "--- 3. 调用 ---\n";
      f1();
      f2();

      cout << "--- 4. 结束 ---\n";
      return 0;
  }