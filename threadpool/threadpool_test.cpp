#include <iostream>
#include <atomic>
#include <thread>
#include "threadpool.hpp"
using namespace std;

int main() {
    atomic<int> done{0};

    {
        ThreadPool pool(4);                       // 四个工人

        for (int i = 0; i < 100; ++i) {
            pool.submit([&done, i]{
                done++;
                if (i % 20 == 0)
                    cout << "任务 " << i << " 由线程 "
                         << this_thread::get_id() << " 执行\n";
            });
        }
    }   // ← pool 在这里析构：close + join

    cout << "全部完成，共 " << done << " 个\n";
    return 0;
}