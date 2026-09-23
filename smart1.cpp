#include<iostream>
#include<memory>
using namespace std;

struct Foo{
    int x = 42;
    Foo(){cout << ">>Foo 构造\n";}
    ~Foo(){cout << ">>Foo 析构\n";}
};

int main(){
   shared_ptr<Foo> a = make_shared<Foo>();
      cout << "计数 = " << a.use_count() << "\n";

      {
          shared_ptr<Foo> b = a;                    // ← 拷贝！unique_ptr做不到的
          cout << "计数 = " << a.use_count() << "\n";
          cout << "b->x = " << b->x << "\n";
          cout << "--- b 要走了 ---\n";
      }                                             // b 出作用域

      cout << "计数 = " << a.use_count() << "\n";
      cout << "--- main 要结束了 ---\n";

      return 0;
}
