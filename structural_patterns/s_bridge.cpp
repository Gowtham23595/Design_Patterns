#include <iostream>
#include <memory>
using namespace std;

class Implementation{
    public:
    virtual void Method1() = 0;
    virtual void Method2() = 0;
    virtual void Method3() = 0;
    virtual ~Implementation() = default;
};

class ConcreteImplementationA : public Implementation{
    public:
    void Method1() override{
        cout << "Concrete Implementation A - Method 1\n";
    }
    void Method2() override{
        cout << "Concrete Implementation A - Method 2\n";
    }
    void Method3() override{
        cout << "Concrete Implementation A - Method 3\n";
    }
};

class ConcreteImplementationB : public Implementation{
    public:
    void Method1() override{
        cout << "Concrete Implementation B - Method 1\n";
    }
    void Method2() override{
        cout << "Concrete Implementation B - Method 2\n";
    }
    void Method3() override{
        cout << "Concrete Implementation B - Method 3\n";
    }
};

class Abstraction{
    protected:
    shared_ptr<Implementation> impl_;
    public:
    Abstraction(shared_ptr<Implementation> impl): impl_(impl){}
    void Operation1(){
        impl_->Method1();
    }
    void Operation2(){
        impl_->Method2();
        impl_->Method3();
    }
};

void clientCode(){
    shared_ptr<ConcreteImplementationA> _ptr = make_shared<ConcreteImplementationA>();
    shared_ptr<Abstraction> _ptrA = make_shared<Abstraction>(_ptr);
    _ptrA->Operation1();
    _ptrA->Operation2();
    _ptrA.reset();
    _ptrA = make_shared<Abstraction>(make_shared<ConcreteImplementationB>());
    _ptrA->Operation1();
    _ptrA->Operation2();
}

int main(){
    clientCode();
}