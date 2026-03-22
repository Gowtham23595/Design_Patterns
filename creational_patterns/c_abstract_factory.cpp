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

class AbstractProductB{
    public:
    virtual void createProductB() = 0;
    virtual ~AbstractProductB(){
        cout << "Destructor AbstractProductB\n";
    };
};

class ProductB1 : public AbstractProductB{
    public:
    void createProductB() override{
        cout << "Product B1 created\n";
    }
    ~ProductB1(){
        cout << "Destructor ProductB2\n";
    };
};

class ProductB2 : public AbstractProductB{
    public:
    void createProductB() override{
        cout << "Product B2 created\n";
    }
    ~ProductB2(){
        cout << "Destructor ProductB2\n";
    };
};

class AbstractFactory{
    public:
    virtual shared_ptr<AbstractProductA> createFactoryProductA() = 0;
    virtual shared_ptr<AbstractProductB> createFactoryProductB() = 0;
    virtual void doOperation() = 0;
    virtual ~AbstractFactory(){
        cout << "Destructor AbstractFactory\n";
    };;
};

class ConcreteFactoryA:public AbstractFactory{
    public:
    shared_ptr<ProductA1>pA;
    shared_ptr<ProductB1>pB;
    ConcreteFactoryA(){
        pA = make_shared<ProductA1>();
        pB = make_shared<ProductB1>();
    }
    shared_ptr<AbstractProductA> createFactoryProductA() override{
        return pA;
    }
    shared_ptr<AbstractProductB> createFactoryProductB() override{
        return pB;
    }

    void doOperation(){
        pA->createProductA();
        pB->createProductB();
    }

    ~ConcreteFactoryA(){
        cout << "Destructor ConcreteFactoryA\n";
    };
};

class ConcreteFactoryB:public AbstractFactory{
    public:
    shared_ptr<ProductA2>pA;
    shared_ptr<ProductB2>pB;
    ConcreteFactoryB(){
        pA = make_shared<ProductA2>();
        pB = make_shared<ProductB2>();
    }
    shared_ptr<AbstractProductA> createFactoryProductA() override{
        return pA;
    }
    shared_ptr<AbstractProductB> createFactoryProductB() override{
        return pB;
    }

    void doOperation(){
        pA->createProductA();
        pB->createProductB();
    }

    ~ConcreteFactoryB(){
        cout << "Destructor ConcreteFactoryB\n";
    };
};

void clientCode(){
    shared_ptr<AbstractFactory> pObj = make_shared<ConcreteFactoryA>();
    pObj->doOperation();
    pObj.reset();
    pObj = make_shared<ConcreteFactoryB>();
    pObj->doOperation();
}

int main()
{
    clientCode();
}