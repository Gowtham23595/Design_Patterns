#include <iostream>
#include <memory>
using namespace std;

class AbstractProductA{
    public:
    virtual void createProductA() = 0;
    virtual ~AbstractProductA() = default;
};

class ProductA1 : public AbstractProductA{
    public:
    void createProductA() override{
        cout << "Created Product A1\n";
    }
    ~ProductA1(){
        cout << "Destructor ProductA1\n";
    };
};

class ProductA2 : public AbstractProductA{
    public:
    void createProductA() override{
        cout<<"Created Product A2\n";
    }
    ~ProductA2(){
        cout << "Destructor ProductA2\n";
    };
};


class AbstractFactory{
    
    public:
    shared_ptr<AbstractProductA> pProductA;
    virtual shared_ptr<AbstractProductA> createFactoryProductA() = 0;
    
    void doOperation(){
        pProductA = createFactoryProductA();
        pProductA->createProductA();
    }
    virtual ~AbstractFactory(){
        cout << "Destructor AbstractFactory\n";
    };;
};

class ConcreteFactoryA:public AbstractFactory{
    public:
    shared_ptr<ProductA1>pA;
    ConcreteFactoryA(){
        pA = make_shared<ProductA1>();
    }
    shared_ptr<AbstractProductA> createFactoryProductA() override{
        return pA;
    }

    ~ConcreteFactoryA(){
        cout << "Destructor ConcreteFactoryA\n";
    };
};

class ConcreteFactoryB:public AbstractFactory{
    public:
    shared_ptr<ProductA2>pA;
    ConcreteFactoryB(){
        pA = make_shared<ProductA2>();
    }
    shared_ptr<AbstractProductA> createFactoryProductA() override{
        return pA;
    }

    ~ConcreteFactoryB(){
        cout << "Destructor ConcreteFactoryB\n";
    };
};

void clientCode(){
    shared_ptr<AbstractFactory> pObj = make_shared<ConcreteFactoryA>();
    pObj->doOperation();
    cout << "B Count = "<<pObj.use_count()<<"\n";
    pObj.reset();
    cout << "A Count = "<<pObj.use_count()<<"\n";
    pObj = make_shared<ConcreteFactoryB>();
    pObj->doOperation();
}

int main()
{
    clientCode();
    return 0;
}