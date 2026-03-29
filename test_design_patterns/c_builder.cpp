#include <iostream>
#include <memory>


using namespace std;

class Product{
    public:
    string data;
    Product(string s):data(s){}
    void show(){
        cout << this->data << "\n";
    }
};


class Builder{
    public:
    virtual void reset() = 0;
    virtual ~Builder() = default;
    virtual void buildStep1() = 0;
    virtual void buildStep2() = 0;
    virtual void buildStep3() = 0;
    virtual void buildStep4() = 0;
    virtual shared_ptr<Product> getResult() = 0;
};

class ConcreteBuilderA : public Builder{

    shared_ptr<Product> prd;
    public:
    ConcreteBuilderA(){
        prd = make_shared<Product>("Product A");
    }
    void reset(){
        prd.reset();
        prd = make_shared<Product>("Product A");
    }

    virtual void buildStep1() override{
        prd->data += " Added Step1 "; 
    }
    virtual void buildStep2() override{
        prd->data += " Added Step2 "; 
    }
    virtual void buildStep3() override{
        prd->data += " Added Step3 "; 
    }
    virtual void buildStep4() override{
        prd->data += " Added Step4 "; 
    }

    shared_ptr<Product> getResult(){
        return prd;
    }

};

class ConcreteBuilderB : public Builder{

    shared_ptr<Product> prd;
    public:
    ConcreteBuilderB(){
        prd = make_shared<Product>("Product B");
    }
    void reset(){
        prd.reset();
        prd = make_shared<Product>("Product B");
    }

    virtual void buildStep1() override{
        prd->data = prd->data + " Added Step1 "; 
    }
    virtual void buildStep2() override{
        prd->data = prd->data + " Added Step2 "; 
    }
    virtual void buildStep3() override{
        prd->data = prd->data + " Added Step3 "; 
    }
    virtual void buildStep4() override{
        prd->data = prd->data + " Added Step4 "; 
    }

    shared_ptr<Product> getResult(){
        return prd;
    }

};

class Director{
    shared_ptr<Builder> ptr;
    public:
    Director(shared_ptr<Builder> p): ptr(p) {}

    void make(string type){
        ptr->reset();
        if(type == "simple"){
            ptr->buildStep1();
        }
        else{
            ptr->buildStep2();
            ptr->buildStep3();
            ptr->buildStep4();
        }
    }

    void changeBuilder(shared_ptr<Builder> p){
        ptr.reset();
        ptr = p;
    }
};

void clientCode(){
    shared_ptr<Builder> objBuilder = make_shared<ConcreteBuilderA>();
    unique_ptr<Director> objDirector = make_unique<Director>(objBuilder);
    objDirector->make("simple");
    shared_ptr<Product> product1 = objBuilder->getResult();
    product1->show();
    objBuilder->reset();
    objDirector->make(" ");
    shared_ptr<Product> product2 = objBuilder->getResult();
    product2->show();
    
}

int main(){
    clientCode();
}