#include <iostream>
 
using namespace std;
template<typename T>          // ← 新增这一行：声明 T 是「类型占位符」
class Box {
public:
    T value_;                 // 原来这里写 int
    Box(T v) : value_(v) {}
    T get() { return value_; }
};

int main(){
    Box<int> a(42);
    Box<string> b("abc");
    cout << a.get()<<endl;

    cout<< b.get()<<endl;

    return 0;
}
