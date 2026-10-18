#include <iostream>
#include <cstdlib>
#include "fixedpool.hpp"
#include "../queue/test_check.hpp"
using namespace std;

void test_basic() {
    FixedPool pool(32, 3);

    void* a0 = pool.allocate();       // 准备 + 执行
    void* a1 = pool.allocate();
    void* a2 = pool.allocate();

    CHECK(a0 != nullptr);             // 断言
    CHECK(a1 != nullptr);
    CHECK(a2 != nullptr);
    CHECK(abs((char*)a1 - (char*)a0) == 32);   // 相邻块差 32 字节
    CHECK(abs((char*)a2 - (char*)a1) == 32);
}

void test_exhausted(){
    FixedPool pool(32,3);
    void* a0 =pool.allocate();
    void* a1 =pool.allocate();
    void* a2 =pool.allocate();
    void* a3 =pool.allocate();

    CHECK(a0!=nullptr);
    CHECK(a1!=nullptr);
    CHECK(a2!=nullptr);
    CHECK(a3==nullptr);
   
}
void test_reuse() {
    FixedPool pool(32, 3);

    void* a0 = pool.allocate();      // 取一块
    pool.deallocate(a0); 
    void* a1 = pool.allocate();                   // 还回去
    CHECK(a0 == a1);                 // 再取一块，断言它 == 刚才那块
}



int main() {
    test_basic();
    if (g_failures == 0) cout << "全部通过\n";
    else                 cout << g_failures << " 条失败\n";
    return g_failures == 0 ? 0 : 1;
}