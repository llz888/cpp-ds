#include <iostream>
  #include <memory>
  using namespace std;

  struct Node {
      int id;
      weak_ptr<Node> next;          // ← 指向下一个
      Node(int i) : id(i) { cout << ">> Node " << i << " 构造\n"; }
      ~Node() { cout << ">> Node " << id << " 析构\n"; }
  };

  int main() {
      {
          shared_ptr<Node> a = make_shared<Node>(1);
          shared_ptr<Node> b = make_shared<Node>(2);

          a->next = b;      // 1 指向 2
          b->next = a;      // 2 指向 1     ← 这就是"环"

          cout << "a 的计数 = " << a.use_count() << "\n";
          cout << "b 的计数 = " << b.use_count() << "\n";
          cout << "--- 作用域要结束了 ---\n";
      }
      cout << "--- 出来了 ---\n";
      return 0;
  }