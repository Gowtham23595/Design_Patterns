#include <iostream>
#include <memory>

using namespace std;

class Singleton{
public:
    int data;    
    static shared_ptr<Singleton> pS;

    Singleton(int val) {
        data = val;
    }
    Singleton(Singleton& other) = delete;
    void operator=(Singleton& other) = delete;
    static shared_ptr<Singleton> getInstance(int val){
        if (pS == nullptr){
            pS = make_shared<Singleton>(val);
        }
        return pS;
    }
};

shared_ptr<Singleton> Singleton::pS = nullptr;

int main(){
    shared_ptr<Singleton> p = Singleton::getInstance(20);
    cout << p->data;
    return 0;
}
