#include <iostream>
#include <memory>
using namespace std;

class Component{
    public:
    virtual string operation() = 0;
    virtual ~Component() = default;
};

class ConcreteComponent : public Component{
    public:
    string operation() override{
        return "Concrete Component";
    }
};

class Decorator : public Component{
    public:
    shared_ptr<Component> _pC;

    Decorator(const shared_ptr<Component> &p){
        _pC = p;
    }

    string operation() override{
       return _pC->operation();
    }
};

class ConcreteDecorator1 : public Decorator{
    public:
    ConcreteDecorator1(const shared_ptr<Component> p) : Decorator(p){}
    string operation() override{
        return "Concrete Decorator 1 " + _pC->operation() + " ";
    }
};

class ConcreteDecorator2 : public Decorator{
    public:
    ConcreteDecorator2(const shared_ptr<Component> p) : Decorator(p){}
    string operation() override{
        return "Concrete Decorator 2 " + _pC->operation() + " ";
    }
};

void ClientCode(){
    shared_ptr<Component> ptr = make_shared<ConcreteComponent>();
    shared_ptr<ConcreteDecorator1> ptr1 = make_shared<ConcreteDecorator1>(ptr);
    shared_ptr<ConcreteDecorator2> ptr2 = make_shared<ConcreteDecorator2>(ptr1);
    cout << ptr2->operation();

}

int main(){
    ClientCode();
}