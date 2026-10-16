#pragma once
#include <functional>
#include <thread>
#include <vector>
#include <cstddef>
#include "../queue/blocking_queue.hpp"

using namespace std;

class ThreadPool {
private:
    BlockingQueue<std::function<void()>> q_;
    std::vector<std::thread>             workers_;

    void worker() {
        function<void()> v;
        while (q_.pop(v)) {
            try { v(); } catch (...) { }      // 异常绝不许穿出线程函数
        }
    }

public:
    explicit ThreadPool(std::size_t n, std::size_t cap = 1024)
    : q_(cap)                                  // ← 必须在这儿给它容量
    {
        for (std::size_t i = 0; i < n; ++i)
            workers_.emplace_back([this]{ worker(); });
    }

    ~ThreadPool() {
        q_.close();                            // 顺序不能反
        for (auto& t : workers_) t.join();
    }

    template<typename F>
    void submit(F f) {
        q_.push(std::function<void()>(f));
    }
};