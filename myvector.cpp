#include <iostream>
using namespace std;

template<typename T>
class MyVector {
public:
    MyVector() : data_(nullptr), size_(0), cap_(0) {}
    ~MyVector() { delete[] data_; }
    //拷贝构造
    MyVector(const MyVector& other) {
        data_ = new T[other.cap_];
        for(int i = 0;i<other.size_;++i)
            this->data_[i] = other.data_[i];
        this->size_= other.size_;
        this->cap_ = other.cap_;
    }
    //拷贝赋值
    MyVector& operator=(const MyVector& other) {
        if(this == &other) return *this;
        T* newdata_ = new T[other.cap_];
        for(int i = 0;i<other.size_;++i)
            newdata_[i] = other.data_[i];
        delete[] data_;
        this->data_ = newdata_;
        this->size_ = other.size_;
        this->cap_ = other.cap_;

        return *this;
    }
    //移动构造
    MyVector(MyVector&& other) noexcept {
        data_ = other.data_;
        size_ = other.size_;
        cap_ = other.cap_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.cap_ = 0;
    }
    //移动赋值
    MyVector& operator=(MyVector&& other) noexcept {
        if(this == &other) return *this;
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        cap_ = other.cap_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.cap_ = 0;
        
        return *this;
    }
    void push_back(const T& v) {
        if (size_ == cap_) grow();      // ← 满了就扩容
        data_[size_++] = v;
    }

    T& operator[](int i) { return data_[i]; }
    int size() const { return size_; }
    int capacity() const { return cap_; }

private:
    T* data_;
    int size_;
    int cap_;

    void grow() {
        int n = cap_ ==0?1 : cap_*2;
        T* data = new T[n];
        for(int i = 0;i<size_;++i){
            data[i] = data_[i];
        }        // ★ 你来写。就三个动作：申请更大的 → 搬 → 释放旧的
        delete[] data_;
        data_ =data;
        cap_=n;
    }
};
#include <utility>          // std::move 在这（保险起见加上）

int main() {
    MyVector<int> a;
    for (int i = 0; i < 3; ++i) a.push_back(i);

    MyVector<int> b;
    b.push_back(99);              // ← b 先自己占一块内存

    b = std::move(a);             // ← 移动赋值

    cout << "b 里有 " << b.size() << " 个\n";
    cout << "a 里有 " << a.size() << " 个\n";
    return 0;
}