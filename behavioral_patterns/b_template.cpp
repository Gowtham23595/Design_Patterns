#include <iostream>
#include <memory>
using namespace std;

class Base{
    public:
    void TemplateMethod(){
        this->baseOperation1();
        this->baseOperation2();
        this->requiredOperation1();
    }
    protected:
    void baseOperation1(){
        cout << "Inside Based Operation\n";
    }
    void baseOperation2(){
        cout << "Inside Based Operation 2\n";
    }
    virtual void requiredOperation1()= 0;
};

class ConcreteClass1:public Base{
    public:
    void requiredOperation1() override{
        cout << "Concreted1 Required Operation\n";
    }
};

class ConcreteClass2:public Base{
    public:
    void requiredOperation1() override{
        cout << "Concrete2 Required Operation\n";
    }
};

void clientCode(){
    unique_ptr<Base> ptr = make_unique<ConcreteClass1>();
    ptr->TemplateMethod();

    ptr.reset();
    ptr = make_unique<ConcreteClass2>();
    ptr->TemplateMethod();
}

int main(){
    clientCode();
}

