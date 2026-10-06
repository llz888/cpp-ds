#pragma once 

template<typename T>

class MyUniquePtr{
public:
    explicit MyUniquePtr(T* p = nullptr) : ptr_(p){}
    ~MyUniquePtr(){delete ptr_;}

    MyUniquePtr(const MyUniquePtr&) = delete;
    MyUniquePtr& operator=(const MyUniquePtr&) = delete;

    MyUniquePtr(MyUniquePtr&& other) noexcept {
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }
    MyUniquePtr& operator=(MyUniquePtr&& other) noexcept {
        if(this == &other)  return *this;
        delete ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
        return *this;
    }

    T* operator->() const {return ptr_;}
    T& operator*() const {return *ptr_;}
    T* get() const {return ptr_;}


private:
    T* ptr_;

};
