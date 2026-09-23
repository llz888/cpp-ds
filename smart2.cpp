#include <iostream>
  #include <memory>
  using namespace std;

  struct Foo { int x = 42; };

  int main() {
      cout << "裸指针                sizeof = " << sizeof(Foo*) << "\n";
      cout << "unique_ptr<Foo>       sizeof = " << sizeof(unique_ptr<Foo>)
  << "\n";
      cout << "shared_ptr<Foo>       sizeof = " << sizeof(shared_ptr<Foo>)
  << "\n";
      return 0;
  }
