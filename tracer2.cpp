#include <cstdio>

struct Tracer{
    const char* name;
    Tracer(const char* n) : name(n) { printf("构造 %s\n",name);}
    ~Tracer() {printf("析构 %s\n", name);}
};

int main(){
    Tracer a("栈上的");
    Tracer* p = new Tracer("堆上的");
    printf("--- main 结束 --- \n");
    return 0;
}