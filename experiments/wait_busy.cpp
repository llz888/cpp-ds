#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>



using namespace std;
atomic<bool> ready{false};


void worker(){
    while(!ready.load()){}
    cout << "worker:收到"<<endl;
}


int main(){
    thread t1(worker);
    this_thread::sleep_for(1s);
    ready = true;
    t1.join();

    return 0;
}