#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <cstddef>

template<typename T>
class BlockingQueue {
public:
    explicit BlockingQueue(std::size_t cap) : cap_(cap), closed_(false) {}

    void push(const T& v) {
        std::unique_lock<std::mutex> lk(mtx_);
        notFull_.wait(lk, [this]{ return q_.size() < cap_; });
        q_.push(v);
        notEmpty_.notify_one();                                  // V(full)
    }

    // 返回 false 表示：队列已关闭、而且已经取空了
    bool pop(T& out) {
        std::unique_lock<std::mutex> lk(mtx_);
        notEmpty_.wait(lk, [this]{ return !q_.empty() || closed_; });
        if (q_.empty()) return false;        // 被叫醒是因为"打烊"，而且已经取空
        out = q_.front();
        q_.pop();
        notFull_.notify_one();                                   // V(empty)
        return true;
    }

    void close() {
        std::lock_guard<std::mutex> lk(mtx_);
        closed_ = true;
        notEmpty_.notify_all();              // 打烊 —— 叫醒所有人
    }

private:
    std::queue<T>           q_;
    std::size_t             cap_;
    std::mutex              mtx_;
    std::condition_variable notFull_;
    std::condition_variable notEmpty_;
    bool                    closed_;
};