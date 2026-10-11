#include <iostream>
#include <thread>
#include "blocking_queue.hpp"
#include "test_check.hpp"
using namespace std;

// ① 基本 push / pop
void test_basic() {
    BlockingQueue<int> q(3);
    q.push(1);
    q.push(2);
    int v;
    CHECK(q.pop(v) && v == 1);
    CHECK(q.pop(v) && v == 2);
}

// ② 打烊之后 pop 立刻返回 false（不然就是死锁）
void test_close() {
    BlockingQueue<int> q(3);
    q.close();
    int v;
    CHECK(q.pop(v) == false);
}

// ③ 并发下不丢不多 —— 这条最值钱
void test_no_loss() {
    BlockingQueue<int> q(8);
    long sum = 0;

    thread p([&]{
        for (int i = 1; i <= 1000; ++i) q.push(i);
        q.close();
    });

    int v;
    while (q.pop(v)) sum += v;
    p.join();

    CHECK(sum == 500500);      // ← 从 1 改回来          // 1+2+...+1000，一个没丢一个没重
}

int main() {
    test_basic();
    test_close();
    test_no_loss();

    if (g_failures == 0) cout << "全部通过\n";
    else                 cout << g_failures << " 条失败\n";
    return g_failures == 0 ? 0 : 1;
}