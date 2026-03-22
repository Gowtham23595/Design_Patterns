#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>

using namespace std;

enum class Type : int32_t{
    PROTOTYPE_1 = 0,
    PROTOTYPE_2
};

class Prototype{
    public:
    string prototype_name;
    float prototype_value;

    Prototype(string name, float value) : prototype_name(name), prototype_value(value){}

    virtual ~Prototype() = default;
    virtual shared_ptr<Prototype> clone() = 0;
    void method(float value){
        this->prototype_value = value;
        cout << "Name : "<<prototype_name << "Value : "<<prototype_value<<"\n";
    }
    void method(){
        cout << "Name : "<<prototype_name << "Value : "<<prototype_value<<"\n";
    }
};

class ConcreteProtoType1 : public Prototype{
    public:
    ConcreteProtoType1(string name, float value ): Prototype(name,value){}
    shared_ptr<Prototype> clone()override{
        return make_shared<ConcreteProtoType1>(this->prototype_name,this->prototype_value);
    }
};

class ConcreteProtoType2 : public Prototype{
    public:
    ConcreteProtoType2(string name, float value ): Prototype(name,value){}
    shared_ptr<Prototype> clone()override{
        return make_shared<ConcreteProtoType2>(this->prototype_name,this->prototype_value);
    }
};

class PrototypeFactory{
    public:
    unordered_map<Type,shared_ptr<Prototype>> facObj;

    PrototypeFactory(){
        facObj[Type::PROTOTYPE_1] = make_shared<ConcreteProtoType1>("Prototype1", 20.0);
        facObj[Type::PROTOTYPE_2] = make_shared<ConcreteProtoType2>("Prototype2", 40.0);
    }

    shared_ptr<Prototype> createPrototype(Type t){
        return facObj[t]->clone();
    }

};

void clientCode(){
    unique_ptr<PrototypeFactory> pfObj = make_unique<PrototypeFactory>();
    shared_ptr<Prototype> prototype1 = pfObj->createPrototype(Type::PROTOTYPE_1);
    prototype1->method();
    prototype1->method(10);
    shared_ptr<Prototype> prototype2 = pfObj->createPrototype(Type::PROTOTYPE_2);
    prototype2->method();
    prototype2->method(10);


}

int main(int argc, char* argv[]){
    clientCode();
}
