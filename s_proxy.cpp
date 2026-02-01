#include <iostream>
#include <memory>
using namespace std;

class Subject{
    public:
    virtual void request() = 0;
};

class RealSubject : public Subject{
    public:
    RealSubject() = default;
    void request() override{
        cout << "Using the actual Service\n";
    }
};

class Proxy : public Subject{
    public:
    shared_ptr<RealSubject> realObj;

    Proxy(shared_ptr<RealSubject> obj): realObj(obj){}

    void request(){
        cout << "Checking via proxy\n";
        realObj->request();
        cout << "Checking via proxy completed\n";
    }
};

void clientCode(shared_ptr<Subject> s){
    s->request();
}

int main(int argc,char* argv[]){
    shared_ptr<RealSubject> R1 = make_shared<RealSubject>();
    R1->request();

    shared_ptr<Proxy> P1 = make_shared<Proxy>(R1);
    P1->request();
}