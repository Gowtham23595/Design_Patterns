#include <iostream>
#include <memory>



//Object adapter
class Target{
    public:
    virtual void request(){
        std::cout << "Called Target request method\n";
    }
};

class Adaptee{
    public:
    void specificRequest(){
        std::cout << "Called Adaptee specific request method\n";
    }
};

class Adapter : public Target{
    public:
    std::shared_ptr<Adaptee> adaptee_;
    Adapter(std::shared_ptr<Adaptee> obj):adaptee_(obj){}
    void request() override{
        adaptee_->specificRequest();
    }
};

void clientCode(){
    std::shared_ptr<Target> pT = std::make_shared<Target>();
    pT->request();
    pT.reset();
    std::shared_ptr<Adaptee> _ptr = std::make_shared<Adaptee>();
    std::shared_ptr<Adapter> _ptr_new = std::make_shared<Adapter>(_ptr);
    pT = _ptr_new;
    pT->request();
}

int main(){
    clientCode();
}