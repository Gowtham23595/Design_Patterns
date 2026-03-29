#include <iostream>
#include <thread>
#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

void add(int x, int y){
    cout << "Add: "<<x+y<<"\n";
}
void sub(int x, int y){
    cout << "Sub: "<<x-y<<"\n";
}
void mul(int x, int y){
    cout << "Mul: "<<x*y<<"\n";
}
void divs(int x, int y){
    cout << "divs: "<<x/y<<"\n";
}

class ThreadPool{
    private:
    vector<thread> workers;
    queue<function<void()>> tasks;
    mutex mtx;
    condition_variable cv;
    bool stop = false;

    public:
    ThreadPool(int n){
        for (int i = 0; i < n; i++){
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

    void enqueue(function<void()> fn){
        {
            lock_guard<mutex> lock(mtx);
            tasks.push(std::move(fn));
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

int main(int argc, char* argv[]){
    ThreadPool obj(2);
    obj.enqueue([]{add(10,3);});
    obj.enqueue([]{add(20,3);});
    obj.enqueue([]{add(30,3);});
    obj.enqueue([]{add(40,3);});
    obj.enqueue([]{add(50,3);});
}


