#include<iostream>
#include<memory>

using namespace std;

class Context;

class State{
    public:
    shared_ptr<Context> context_;

    void setContext(shared_ptr<Context> c){
        cout << "Setting Context \n";
        context_ = c;
    }

    virtual void handle1() = 0;
    virtual void handle2() = 0;
};

class ConcreteStateA : public State{
    public:
    void handle1() override;
    void handle2() override{
        cout << "In Concrete Class A Handle 2\n";
    }
};

class ConcreteStateB: public State{
    public:
    void handle1() override{
        cout << "IN Concrete Class B Handle 1\n";
    }
    void handle2() override{
        cout << "In Concrete Class B Handle 2\n";
    }
};


class Context : public enable_shared_from_this<Context>{
    public:
    shared_ptr<State> state_;
    Context(shared_ptr<State> s){
        state_.reset();
        state_ = s;
    }

    void init(){
        state_->setContext(shared_from_this());
    }

    void setTransition(shared_ptr<State> s){
        cout << "Transition Happening\n";
        state_.reset();
        state_ = s;
        s->setContext(shared_from_this());
    }

    void request1(){
        state_->handle1();
    }
    void request2(){
        state_->handle2();
    }
};

void ConcreteStateA::handle1(){
        cout << "IN Concrete Class A Handle 1\n";
        this->context_->setTransition(make_shared<ConcreteStateB>());
}

void clientCode(){
    shared_ptr<State> s = make_shared<ConcreteStateA>();
    shared_ptr<Context> c = make_shared<Context>(s);
    c->init();
    c->request1();
    c->request2();

}

int main(){
    clientCode();
}