#include<cstdio>
#include<cstring>

class Buffer{
public:
    Buffer(int size) : size_(size){
        data_ = new char[size];
    }
    ~Buffer(){
        delete[] data_;
    }

    Buffer(const Buffer& other) : size_(other.size_){
        data_ = new char[size_];
        memcpy(data_, other.data_,size_);
        printf(">> 拷贝构造！ 又分配了%d 字节\n",size_);
    }

private:
    char* data_;
    int size_;    

};

int main(){
    Buffer big(100* 1024*1024);
    printf("---开始拷贝---\n");
    Buffer copy = big;
    printf("---结束---\n");
    return 0;
}