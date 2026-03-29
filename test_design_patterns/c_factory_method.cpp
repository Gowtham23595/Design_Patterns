#include <iostream>
#include <memory>

using namespace std;

class ProductA{
    public:
    virtual void useProduct() = 0;
    virtual ~ProductA() = default;
};

class ProductA1 : public ProductA{
    public:
    void useProduct()override{
        cout << "Creating Product A1\n";
    }
    ~ProductA1() = default;

};

class ProductA2: public ProductA{
    public:
    void useProduct()override{
        cout << "Creating Product A2\n";
    }
};

class Factory{
    public:
    virtual shared_ptr<ProductA> createFactoryProductA() = 0; 
    virtual ~Factory() = default;
    void doOperation(){
        shared_ptr<ProductA> prdA = createFactoryProductA();
        prdA->useProduct();
    }
};

class ConcreteFactoryA : public Factory{
    public:
    ConcreteFactoryA() = default;
    
    shared_ptr<ProductA> createFactoryProductA()override{
        return make_shared<ProductA1>();
    }
};

class ConcreteFactoryB : public Factory{
    public:
    ConcreteFactoryB()=default;
    shared_ptr<ProductA> createFactoryProductA()override{
        return make_shared<ProductA2>();
    }
};

void clientCode(shared_ptr<Factory> ptr){
    ptr->doOperation();
}

int main(){
    shared_ptr<Factory> ptr = make_shared<ConcreteFactoryA>();
    clientCode(ptr);
    ptr.reset();
    ptr = make_shared<ConcreteFactoryB>();
    clientCode(ptr);
}

