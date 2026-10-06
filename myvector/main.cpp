#include <iostream>
#include "myvector.hpp"
#include <algorithm>



using namespace std;



int main() {
    MyVector<int> v;
    for (int i = 1; i <= 5; ++i) v.push_back(i * 10);

    cout << "size=" << v.size() << " front=" << v.front() << " back=" << v.back() << "\n";

    v.pop_back();
    cout << "pop 之后: size=" << v.size() << " back=" << v.back() << "\n";

    v.clear();
    cout << "clear 之后: size=" << v.size()
         << " capacity=" << v.capacity() << " empty=" << v.empty() << "\n";
    return 0;
}