#include <iostream>
using namespace std;

int main() {
    int x = 1;

    auto f1 = [x]() { cout << "f1: " << x << "\n"; };
    auto f2 = [&x]() { cout << "f2: " << x << "\n"; };

    x = 99;    // ← 捕获之后再改

    f1();
    f2();

    return 0;
}