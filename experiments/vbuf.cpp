#include<cstdio>
#include<cstring>
#include<vector>

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
        printf(">> 拷贝构造！\n");

    }

private:
    char* data_;
    int size_;    
};
 int main() {
      std::vector<Buffer> v;
      for (int i = 0; i < 5; i++) {
          printf("--- 第 %d 次 push_back ---\n", i);
          v.push_back(Buffer(1024 * 1024));    // 1 MB
      }
      printf("--- 结束，vector 里只有 %zu 个元素 ---\n", v.size());
      return 0;
  }