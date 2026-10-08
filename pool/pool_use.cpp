#include<iostream>
#include"fixedpool.hpp"


using namespace std;

class Foo{
public:
    int x_;
    Foo(int x):x_(x){
        cout<<">> 构造 x="<<x_<<endl;
    }
    ~Foo(){
        cout<<">> 析构 x="<<x_<<endl;
    }
};


int main(){
    FixedPool pool(8,10);
    void* raw = pool.allocate();
    cout<< raw<<endl;
    Foo* f = new(raw) Foo(7);
    cout << "f->x" <<f->x_<< endl;
    f->~Foo();
    pool.deallocate(raw);
    return 0;
}