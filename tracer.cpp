#include<cstdio>

struct Tracer{
    const char* name;
    Tracer(const char* n):name(n){printf("构造 %s\n",name);}
    ~Tracer() {printf("析构 %s\n",name);}

};

Tracer global("全局");

int main(){
    printf("---main 开始 ---\n");
    Tracer a("a");
    {
        Tracer b("b");
        printf("--- 内层作用域末尾 ---\n");
    }
    printf("--- main 即将结束 ---\n");
    return 0;
}