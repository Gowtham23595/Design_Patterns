#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>

using namespace std;

class CountingSemaphore{
    private:
    condition_variable cv;
    mutex mtx;
    int count{};

    public:
    CountingSemaphore(int size = 3):count(size){}

    void acquire(){
        unique_lock<mutex> lock(mtx);
        cv.wait(lock,[this]{return count > 0;});
        count--;
    }
    void release(){
        {
            lock_guard<mutex> lg(mtx);
            count++;
        }
        cv.notify_one();
    }
};

CountingSemaphore sem(3);

void consumer()
{
    cout << "Consuming\n";
    sem.acquire();
    cout << "Consumed\n";
}

void producer(){
    cout << "producing\n";
    sem.release();
    cout <<"produced\n";
}

int main()
{
    thread t1(consumer);
    thread t3(consumer);
    thread t4(consumer);
    thread t5(consumer);

    this_thread::sleep_for(chrono::seconds(2));
    thread t2(producer);

    t2.join();
    t1.join();
    t3.join();
    t4.join();
    t5.join();

}
