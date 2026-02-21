#include <iostream>
#include <memory>   
using namespace std;

class Strategy{
    public:
    virtual void run(int a, int b) = 0;
};

class ConcreteClassA: public Strategy{
    public:
    void run(int a, int b) {
        cout << "Running Algorithm A " << a + b << "\n";
    }
};

class ConcreteClassB : public Strategy{
    public:
    void run(int a , int b){
        cout << "Running Algorithm B " << a * b << "\n";
    }
};

class Context{
    public:
    shared_ptr<Strategy> p_;
    Context(shared_ptr<Strategy> p){
        p_ = p;
    }

    void set(shared_ptr<Strategy> p){
        p_.reset();
        p_ = p;
    }

    void doOPeration(int a, int b){
        p_->run(a,b);
    }
};

void clientCode(){
    shared_ptr<Strategy> pCA = make_shared<ConcreteClassA>();
    unique_ptr<Context> pC = make_unique<Context>(pCA);
    pC->doOPeration(10,20);
    shared_ptr<Strategy> pCB = make_shared<ConcreteClassB>();
    pC->set(pCB);
    pC->doOPeration(10,20);
}

int main(){
    clientCode();
}