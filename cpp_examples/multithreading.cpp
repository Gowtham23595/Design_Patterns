#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <functional>
#include <queue>

using namespace std;

mutex print_mtx;

class ThreadPool{
private:
    vector<thread> workers;
    queue<function<void()>> tasks;
    mutex mtx;
    condition_variable cv;
    bool stop = false;

public:
    ThreadPool(int n){
        for (int i = 0; i < n ; i++){
            workers.emplace_back([this](){
                while(true){
                    function<void()> task;
                    {
                    unique_lock<mutex> lock(mtx);
                    cv.wait(lock,[this]{return stop || !tasks.empty();});
                    if(stop && tasks.empty()){
                        return;
                    }
                    task = std::move(tasks.front());
                    tasks.pop();
                    }
                task();  
                }
            });
        }
    }
    void enqueue(function<void()> task){
        {
        lock_guard<mutex> lock(mtx);
        tasks.push(std::move(task));
        }
        cv.notify_one();
    }
    ~ThreadPool(){
        {
            lock_guard<mutex> lock(mtx);
            stop = true;
        } 
        cv.notify_all();
        for(auto &t : workers){
            t.join();
        }
    }
};

void add(int a, int b){
    lock_guard<mutex> lock(print_mtx);
    cout << "Add:"<<a + b<<"\n";
}
void sub(int a, int b){
    lock_guard<mutex> lock(print_mtx);
    cout << "Sub:"<<a-b<<"\n";
}
void mul(int a, int b){
    lock_guard<mutex> lock(print_mtx);
    cout << "Mul:"<<a*b<<"\n";
}
void divs(int a, int b){
    lock_guard<mutex> lock(print_mtx);
    cout << "Div:"<<a/b<<"\n";
}
int main(){
    ThreadPool obj(2);
    obj.enqueue([]{add(10,5);});
    obj.enqueue([]{add(10,5);});
    obj.enqueue([]{sub(10,5);});
    obj.enqueue([]{mul(10,5);});
    obj.enqueue([]{divs(10,5);});
}
