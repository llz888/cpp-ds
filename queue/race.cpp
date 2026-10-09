#include <iostream>
#include <thread>
#include <mutex>

using namespace std;


mutex mtx;
int counter = 0;
void add(){
    lock_guard<mutex> guard(mtx);
    for(int i =0;i<100000;i++)
    {
        
        counter++;
        

    }   
}
int main(){
    thread t1(add);
    thread t2(add);
    t1.join();
    t2.join();


    cout << counter<< endl;


}