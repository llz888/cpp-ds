#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v;
    for (int i = 0; i < 12; ++i) {
        v.push_back(i);
        cout << "装了几个 = " << v.size() << "    最多能装 = " << v.capacity() << "\n";
    }
    return 0;
}