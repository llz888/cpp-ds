#pragma once

template<typename T>
class MySharedPtr {
public:
    // 出生：在堆上分配一个计数器，初值 1
    explicit MySharedPtr(T* p = nullptr)
        : ptr_(p), count_(p ? new int(1) : nullptr) {}

    // 拷贝：共享同一个指针和同一个计数器，计数 +1
    MySharedPtr(const MySharedPtr& o)
        : ptr_(o.ptr_), count_(o.count_) {       // ← 只拷指针，不拷计数器的值
        if (count_) ++*count_;
    }

    // 死：计数 -1，减到 0 才真的删
    ~MySharedPtr() {
        if (count_ && --*count_ == 0) {
            delete ptr_;
            delete count_;
        }
    }

    T* get() const { return ptr_; }
    int count() const { return count_ ? *count_ : 0; }

private:
    T*   ptr_;
    int* count_;        // ← 指向堆上的计数器，所有副本共用这一个
};