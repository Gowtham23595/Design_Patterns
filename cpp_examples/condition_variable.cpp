#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

using namespace std;
mutex print_mtx;

template<typename T>
class ThreadSafeQueue{
    public:
    queue<T> q;
    mutex mtx;
    condition_variable not_full;
    condition_variable not_empty;
    size_t max_size;

    ThreadSafeQueue(size_t s):max_size(s){
    } 

    void push(T val){
        unique_lock<mutex> lock(mtx);
        not_full.wait(lock,[this]{return q.size() < max_size;});
        q.push(val);
        lock.unlock();
        not_empty.notify_one();
    }

    void wait_and_pop(T& val){
        unique_lock<mutex> lock(mtx);
        not_empty.wait(lock,[this] {return !q.empty();});
        val = q.front();
        q.pop();
        lock.unlock();
        not_full.notify_one();
    }

};

void producer(ThreadSafeQueue<int> &obj){
    for(int i = 0; i <= 5; i++){
        obj.push(i);
        {
        lock_guard<mutex> g(print_mtx);
        cout << "Produced 1 : "<<i<<"\n";
        }
    }
}

void producer2(ThreadSafeQueue<int> &obj){
    for(int i = 0; i <= 5; i++){
        obj.push(i+10);
        {
        lock_guard<mutex> g(print_mtx);
        cout << "Produced 2 : "<<i+10<<"\n";
        }
    }
}

void consumer(ThreadSafeQueue<int> &obj){
    for(int i =0 ; i <= 5; i++){
        int val;
        obj.wait_and_pop(val);
        {
        lock_guard<mutex> g(print_mtx);
        cout << "Consumed 1: "<<val <<"\n";
        }
    }
}

void consumer2(ThreadSafeQueue<int> &obj){
    for(int i =0 ; i <= 5; i++){
        int val;
        obj.wait_and_pop(val);
        {
        lock_guard<mutex> g(print_mtx);
        cout << "Consumed 2: "<<val <<"\n";
        }    
    }
}

int main(){
    ThreadSafeQueue<int> obj(5);
    thread t2(consumer,std::ref(obj));
    thread t1(producer,std::ref(obj));
    thread t3(consumer2,std::ref(obj));
    thread t4(producer2,std::ref(obj));


    t1.join();
    t2.join();
    t3.join();
    t4.join();
}
