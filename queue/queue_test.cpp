#include <iostream>
#include <thread>
#include "blocking_queue.hpp"
using namespace std;
BlockingQueue<int> q(5);

void produce(){
    for(int i = 1;i<=20;i++)
    {    
        q.push(i);
        cout << ("放:" + to_string(i) + "\n");     // 只有一次 <<

    }
}
void consume() {
    int v;
    while (q.pop(v)) {                       // ← 返回 false 就跳出
        cout << "取 " << v << "\n";
    }
    cout << "-- 消费者：打烊了，下班 --\n";
}


int main() {

    thread p(produce);
    thread c(consume);

    p.join();            // 等生产者干完
    q.close();           // ← 宣布打烊
    c.join();

    return 0;
}