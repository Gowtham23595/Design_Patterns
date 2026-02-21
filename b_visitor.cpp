#include <iostream>
#include <memory>
using namespace std;    

class ConcreteComponentA;
class ConcreteComponentB;

class Visitor{
    public:
    virtual void visitorConcreteComponentA(shared_ptr<ConcreteComponentA> p) = 0;
    virtual void visitorConcreteComponentB(shared_ptr<ConcreteComponentB> p) = 0;
};

class Element: public enable_shared_from_this<Element>{
    public:
    virtual void accept(shared_ptr<Visitor> p) = 0;
};

class ConcreteComponentA : public Element{
    public:
    void accept(shared_ptr<Visitor> p){
        p->visitorConcreteComponentA(static_pointer_cast<ConcreteComponentA>(shared_from_this()));
    }
    string getData(){
        return "A";
    }
};

class ConcreteComponentB : public Element{
    public:
    void accept(shared_ptr<Visitor> p){
        p->visitorConcreteComponentB(static_pointer_cast<ConcreteComponentB>(shared_from_this()));

    }
    string getData(){
        return "B";
    }
};

class ConcreteVisitorA:public Visitor{
    public:
    void visitorConcreteComponentA(shared_ptr<ConcreteComponentA> p)override{
        cout << p->getData()  << " Visitor A Concrete Component A\n";
    }
    void visitorConcreteComponentB(shared_ptr<ConcreteComponentB> p)override{
        cout << p->getData() << " Visitor A Concrete Component B\n";
    }
};

class ConcreteVisitorB: public Visitor{
    public:
    void visitorConcreteComponentA(shared_ptr<ConcreteComponentA> p)override{
        cout << p->getData()  << " Visitor B Concrete Component A\n";
    }
    void visitorConcreteComponentB(shared_ptr<ConcreteComponentB> p)override{
        cout << p->getData() << " Visitor B Concrete Component B\n";
    }
};

void ClientCode(){
    shared_ptr<Visitor> pVa = make_shared<ConcreteVisitorA>();
    shared_ptr<Element> pE = make_shared<ConcreteComponentA>();
    pE->accept(pVa);
    pE.reset();
    pE = make_shared<ConcreteComponentB>();
    pE->accept(pVa);

    shared_ptr<Visitor> pVb = make_shared<ConcreteVisitorB>();
    pE = make_shared<ConcreteComponentA>();
    pE->accept(pVb);
    pE.reset();
    pE = make_shared<ConcreteComponentB>();
    pE->accept(pVb);
}

int main(){
    ClientCode();
}