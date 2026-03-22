#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Builder{
    public:
    virtual void buildPartA() = 0;
    virtual void buildPartB() = 0;
    virtual void buildPartC() = 0;
    virtual void reset() = 0;
    virtual ~Builder() = default;
};

class ConcreteBuilder1 : public Builder{
    public:
    std::string product;
    void reset() override{
        product = std::string{};
    }
    void buildPartA()override{
        product = product + "Added Part A in Concrete Builder 1, ";
    }
    void buildPartB() override{
        product = product + "Added Part B in Concrete Builder 1, ";
    }
    void buildPartC() override{
        product = product + "Added Part C in Concrete Builder 1, ";
    }
    std::string getResult(){
        return product;
    }
};

class ConcreteBuilder2 : public Builder{
    public:
    std::string product;
    void reset() override{
        product = std::string{};
    }    
    void buildPartA()override{
        product = product + "Added Part A in Concrete Builder 2, ";
    }
    void buildPartB() override{
        product = product + "Added Part B in Concrete Builder 2, ";
    }
    void buildPartC() override{
        product = product + "Added Part C in Concrete Builder 2, ";
    }
    std::string getResult(){
        return product;
    }
};

class Director{
    shared_ptr<Builder> pBuilder;
    public:
    Director(const shared_ptr<Builder> &p) : pBuilder(p){}
    void changeBuilderType(const shared_ptr<Builder> &p ){
        cout << "Count : "<<pBuilder.use_count()<<"\n";
        pBuilder = p;
    }
    void make(const std::string s){
        pBuilder->reset();
        if(s == "Simple"){
            pBuilder->buildPartA();
        }
        else{
            pBuilder->buildPartB();
            pBuilder->buildPartC();
        }
    }
};

void clientCode(){
    shared_ptr<ConcreteBuilder1> pBuilderObj = make_shared<ConcreteBuilder1>();
    unique_ptr<Director> pDirObj = make_unique<Director>(pBuilderObj);
    pDirObj->make("Simple");
    cout << pBuilderObj->getResult()<<"\n";
    pDirObj->make("Complex");
    cout << pBuilderObj->getResult()<<"\n";

    shared_ptr<ConcreteBuilder2> pBuilderObj2 = make_shared<ConcreteBuilder2>();
    pDirObj->changeBuilderType(pBuilderObj2);
    pDirObj->make("Simple");
    cout << pBuilderObj2->getResult()<<"\n";
    pDirObj->make("Complex");
    cout << pBuilderObj2->getResult()<<"\n";
}

int main(int argc, char* argv[]){
    clientCode();
}