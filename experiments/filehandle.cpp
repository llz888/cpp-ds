#include <cstdio>

class FileHandle{
public: 
    FileHandle(const char* path){
        fp_ = fopen(path,"r");
    }
    ~FileHandle(){
        if(fp_){
            fclose(fp_);
            printf(">> 析构:文件已关闭\n");
        }
    }

    bool valid() const {return fp_ != nullptr;}
    FILE* get() const {return fp_;}
    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;

private:
    FILE* fp_;

};
int main(){
    FileHandle a("test.txt");
    printf("句柄 = %p\n", (void*)a.get());
    return 0;
}