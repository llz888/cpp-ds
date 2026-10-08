 #include <iostream>
  #include <string>
  #include <vector>
  using namespace std;

  class Student {
  public:
      Student(const string& name, int id) : name_(name), id_(id), score_(0)
  {}

      // ★ 五个函数，一个都没有
      //   没有 ~Student
      //   没有拷贝构造 / 拷贝赋值
      //   没有移动构造 / 移动赋值

      int get_score(int s) { score_ = s; return score_; }
      void print_score() { cout << name_ << "的分数是：" << score_ << "\n";
  }

  private:
      string name_;                 // ← 注意：不是 char*
      int id_, score_;
  };

  int main() {
      Student s1("多吉", 1);
      Student s2("老王", 2);
      s1.get_score(99);

      cout << "--- 测试1：拷贝赋值 ---\n";
      s2 = s1;
      cout << "s2: "; s2.print_score();

      cout << "--- 测试2：自赋值 ---\n";
      s2 = s2;
      cout << "s2: "; s2.print_score();

      cout << "--- 测试3：移动赋值 ---\n";
      Student s4("老王", 4);
      s4 = std::move(s1);
      cout << "s4: "; s4.print_score();

      cout << "--- 测试4：vector 扩容 ---\n";
      vector<Student> v;
      for (int i = 0; i < 5; ++i)
          v.push_back(Student("多吉", i));
      cout << "vector 里有 " << v.size() << " 个元素\n";

      return 0;
  }