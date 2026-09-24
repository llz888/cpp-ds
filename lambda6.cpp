#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> v = {5, 2, 8, 1, 9};

    cout << "--- 1. 从大到小排序 ---\n";
    sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
    for (int x : v) cout << x << " ";
    cout << "\n";

    int k = 6;

    cout << "--- 2. 值捕获 [k] ---\n";
    auto big1 = [k](int x) { return x > k; };
    cout << "大于 " << k << " 的: " << count_if(v.begin(), v.end(), big1) << " 个\n";

    cout << "--- 3. 引用捕获 [&k] ---\n";
    auto big2 = [&k](int x) { return x > k; };
    k = 3;
    cout << "k 改成 3 之后：\n";
    cout << "big1（快照）数: " << count_if(v.begin(), v.end(), big1) << " 个\n";
    cout << "big2（直播）数: " << count_if(v.begin(), v.end(), big2) << " 个\n";

    return 0;
}