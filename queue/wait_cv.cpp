#include <iostream>
#include <mutex>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <chrono>

using namespace std;

mutex mtx;
condition_variable cv;
bool ready = false;

void worker(){
    unique_lock<mutex> lk(mtx);
    cv.wait(lk,[]{return ready;});
    cout<<"worker:收到"<<endl;

}

int main(){
    thread t1(worker);
    this_thread::sleep_for(1s);
    {
        lock_guard<mutex> lk(mtx);
        ready = true;
    }
    cv.notify_one();
    t1.join();

    return 0;
}