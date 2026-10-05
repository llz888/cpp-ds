#include <iostream>
using namespace std;

template<typename T>
class MyVector {
public:
    MyVector() : data_(nullptr), size_(0), cap_(0) {}
    ~MyVector() { delete[] data_; }
    MyVector(const MyVector& other) {
        data_ = new T[other.cap_];
        for(int i = 0;i<other.size_;++i)
            this->data_[i] = other.data_[i];
        this->size_= other.size_;
        this->cap_ = other.cap_;
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
int main() {
    MyVector<int> a;
    for (int i = 0; i < 10; ++i) a.push_back(i);

    MyVector<int> b = a;                 // ← 这次拷一个大的

    cout << "b 里有 " << b.size() << " 个\n";
    for (int i = 0; i < b.size(); ++i) cout << b[i] << " ";
    cout << "\n";
    return 0;
}