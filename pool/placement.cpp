#include <iostream>
using namespace std;

class Foo{
public:
    int x_;
    Foo(int v):x_(v){
        cout<<">> 构造 x="<<x_<<endl;
    }
    ~Foo(){
        cout<<">> 析构 x="<<x_<<endl;
    }


private:
        
};


int main(){   
    char* p = (char*)operator new(sizeof(Foo));   // 替掉 char arr[...]; char* p = arr;
    cout<<(void*)p<<endl;
    Foo* obj = new (p) Foo(42);
    cout<<"obj->x_"<<obj->x_<<endl;
    obj->~Foo();
    cout<<(void*)p<<endl;

    operator delete(p);
    return 0;
}