#include <iostream>
#include <utility>          // std::move 在这（保险起见加上）
#include <algorithm>
#include <vector>
#include <chrono>


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
    const T* begin() const {return data_;}
    const T* end() const {return data_+size_;}
    
    void print(const MyVector<int>& v) {     // ← 注意 const &
        for (int x : v) cout << x << " ";
        cout << "\n";
    }
    void pop_back(){ 
        size_--;
    }        // 删掉最后一个元素
    bool empty() const { return size_ == 0; }   // 是不是空的
    void clear(){ 
        size_ = 0;  
    }        // 清空所有元素

    T& back()  { return data_[size_ - 1]; }   // 最后一个元素
    T& front() { return data_[0]; }           // 第一个元素

private:
    T* data_;
    int size_;
    int cap_;

    void grow() {
        int n = cap_ ==0?1 : cap_*2;
        T* data = new T[n];
        for(int i = 0;i<size_;++i){
            data[i] = data_[i];
        }        
        delete[] data_;
        data_ =data;
        cap_=n;
    }
};


int main() {
    MyVector<int> v;
    for (int i = 1; i <= 5; ++i) v.push_back(i * 10);

    cout << "size=" << v.size() << " front=" << v.front() << " back=" << v.back() << "\n";

    v.pop_back();
    cout << "pop 之后: size=" << v.size() << " back=" << v.back() << "\n";

    v.clear();
    cout << "clear 之后: size=" << v.size()
         << " capacity=" << v.capacity() << " empty=" << v.empty() << "\n";
    return 0;
}