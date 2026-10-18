#include <iostream>
#include "myvector.hpp"
#include "../queue/test_check.hpp"
using namespace std;

void test_push_back()  { 
    MyVector<int> v;
    v.push_back(1);
    CHECK(v.size() ==1);
    CHECK(v.back() == 1);
    
}
void test_pop_back()   { 
    MyVector<int> v;
    v.push_back(1);
    int n =v.size();
    v.pop_back();
    CHECK(v.size() == n -1);
    CHECK(v.size() == 0);      // 从 1 减到 0
}
void test_size_empty() { 
    MyVector<int> v;
    CHECK(v.size() == 0);
    v.push_back(1);
    CHECK(!v.empty());
    v.clear();
    CHECK(v.size() ==0);
    CHECK(v.empty());
}
void test_grow(){ 
    MyVector<int> v;
    for(int i = 0;i<100;i++)
        v.push_back(i);
    CHECK(v.size()==100);
    CHECK(v[0] == 0);
    CHECK(v[50] == 50);
    CHECK(v[99] == 99);
    CHECK(v.capacity()>= 100);
}
void test_copy(){
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
   
    MyVector<int> v2 = v;
    v[0] = 999;
    v.push_back(3);
    CHECK(v2.size()==2);
    CHECK(v2[0] == 1);
}
void test_move(){
    MyVector<int> v;
    v.push_back(1);
    MyVector<int> v2 = move(v);
    CHECK(v2[0] == 1);
    CHECK(v2.size() == 1);
    CHECK(v.size()==0);
}

int main() {
    test_push_back();
    test_pop_back();
    test_size_empty();
    test_grow();
    test_copy();
    test_move();
    if (g_failures == 0) cout << "全部通过\n";
    else                 cout << g_failures << " 条失败\n";
    return g_failures == 0 ? 0 : 1;
}