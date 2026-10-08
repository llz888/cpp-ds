#include <iostream>
 
using namespace std;

class IntBox{
public:
    int value_;
    IntBox(int v) : value_(v){}
    int get(){return value_;}
};
class StringBox{
public:
    string value_;
    StringBox(string v) : value_(v){}
    string get(){return value_;}
};


int main(){
    IntBox a(42);
    cout << a.get()<<endl;
    StringBox b("abc");
    cout<< b.get()<<endl;

    return 0;
}
