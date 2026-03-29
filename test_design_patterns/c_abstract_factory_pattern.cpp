#include <iostream>
#include <memory>

using namespace std;

class ProductA{
    public:
    virtual void createProduct() = 0;
    virtual ~ProductA() = default;
};

class ProductA1 : public ProductA{
    public:
    void createProduct(){
        cout << "Creating Product A1\n";
    }
    ~ProductA1() = default;

};

class ProductA2: public ProductA{
    public:
    void createProduct(){
        cout << "Creating Product A2\n";
    }
};

class ProductB{
    public:
    virtual void createProduct() = 0;
    virtual ~ProductB() = default;

};

class ProductB1 : public ProductB{
    public:
    virtual void createProduct(){
        cout << "Creating Product B1\n";
    }
};

class ProductB2 : public ProductB{
    public:
    virtual void createProduct(){
        cout << "Creating product B2\n";
    }
};

class Factory{
    public:
    virtual shared_ptr<ProductA> createFactoryProductA() = 0; 
    virtual shared_ptr<ProductB> createFactoryProductB() = 0;  
    virtual ~Factory() = default;

};

class ConcreteFactoryA : public Factory{
    public:
    ConcreteFactoryA() = default;
    
    shared_ptr<ProductA> createFactoryProductA(){
        return make_shared<ProductA1>();
    }
    shared_ptr<ProductB> createFactoryProductB(){
        return make_shared<ProductB1>();
    }
};

class ConcreteFactoryB : public Factory{
    public:
    ConcreteFactoryB()=default;
    shared_ptr<ProductA> createFactoryProductA(){
        return make_shared<ProductA2>();
    }
    shared_ptr<ProductB> createFactoryProductB(){
        return make_shared<ProductB2>();
    }
};

void clientCode(shared_ptr<Factory> ptr){
    shared_ptr<ProductA> prdA = ptr->createFactoryProductA();
    shared_ptr<ProductB> prdB = ptr->createFactoryProductB();
    prdA->createProduct();
    prdB->createProduct();
}

int main(){
    shared_ptr<Factory> ptr = make_shared<ConcreteFactoryA>();
    clientCode(ptr);
    ptr.reset();
    ptr = make_shared<ConcreteFactoryB>();
    clientCode(ptr);
}

