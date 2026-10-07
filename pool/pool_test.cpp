#include <iostream>
#include "fixedpool.hpp"
using namespace std;

int main() {
    FixedPool pool(32, 3);

    void* a[3];
    for (int i = 0; i < 3; ++i) a[i] = pool.allocate();

    cout << "三块：\n";
    for (int i = 0; i < 3; ++i) {
        cout << "  " << a[i];
        if (i) cout << "    差值 " << (long)a[i] - (long)a[i - 1];
        cout << "\n";
    }

    cout << "第 4 次（应该是 0）：" << pool.allocate() << "\n";

    pool.deallocate(a[0]);
    cout << "还掉 a[0] 再要一个（应该等于 " << a[0] << "）：" << pool.allocate() << "\n";
    return 0;
}