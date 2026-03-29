#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
using namespace std;


class BinarySemaphore{
    public:
    condition_variable cv;
    mutex mtx;
    bool flag;


    BinarySemaphore(bool f=false) : flag(f){}

    void acquire(){
        unique_lock<mutex> lock(mtx);
        cv.wait(lock,[this]{return flag;});
        flag = false;
    }

    void release(){
        {
        lock_guard<mutex> lg(mtx);
        flag = true;
        }
        cv.notify_one();
    }
};

BinarySemaphore sem(false);

void consumer(){
    cout << "Consuming..\n";
    sem.acquire();
    cout << "consumed\n";
}

void producer(){
    cout << "Producing..\n";
    sem.release();
    cout << "Produced\n";
}

int main()
{
    thread t1(consumer);
    this_thread::sleep_for(chrono::seconds(2));
    thread t2(producer);

    t1.join();
    t2.join();

    return 0;
}