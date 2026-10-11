#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

//atomic<int> counter{0};

atomic<int> total{0};

void add(){
    int counter = 0;
    for(int i =0;i<10000000;i++){
        counter++;  
    }   
    total += counter;
}

int main(){
    thread t1(add);
    thread t2(add);
    t1.join();
    t2.join();


    cout << total<< endl;


}