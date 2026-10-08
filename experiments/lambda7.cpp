#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> v = {5, 2, 8, 1, 9};

    int n = 0;                          // 计数器
    sort(v.begin(), v.end(), [&n](int a, int b) {
        ++n;
        cout << "第" << n << "问: " << a << " 该在 " << b << " 前面吗?\n";
        return a > b;
    });

    cout << "--- 排完 ---\n";
    for (int x : v) cout << x << " ";
    cout << "\n一共问了 " << n << " 次\n";
    return 0;
}