#include <iostream>
#include <unordered_map>

using namespace std;

class SharedState{
    public:
        int length;
        int width;
};

class UniqueState{
    public:
        int height;
};

class Flyweight{
    public:
    SharedState* sharedObj_;

    void operation(UniqueState &u){
        cout << sharedObj_->length << "," << sharedObj_->width << " Unique Obj == "<<u.height<<"\n";
    }
    
};

class FlyweightFactory{
    public:
    unordered_map<string,Flyweight> factorobj;

    FlyweightFactory(){}

    string getkey(SharedState &s){
        return to_string(s.length)+"_"+to_string(s.width);
    }

    Flyweight& getFlyweight(SharedState &s){
        string key = getkey(s);
        if(factorobj.find(key)==factorobj.end()){
            cout << "Flyweight not found, creating new one.\n";
            Flyweight fw;
            fw.sharedObj_ = &s;
            factorobj[key] = fw;
        }else{
            cout << "Reusing existing flyweight.\n";
        }
        return factorobj[key];
    }

};

class Context{
    public:
    Flyweight& flyweight_;
    UniqueState unique_;

    Context(Flyweight& f, UniqueState& u):flyweight_(f),unique_(u){}

    void operation(){
        flyweight_.operation(unique_);
    }
};

void clientCode(){
    FlyweightFactory* factory = new FlyweightFactory();

    SharedState s1{10,20};
    SharedState s2{30,40};
    SharedState s3{10,20};

    UniqueState u1{100};
    UniqueState u2{200};
    UniqueState u3{300};

    Flyweight& fw1 = factory->getFlyweight(s1);
    Context c1(fw1,u1);
    c1.operation();

    Flyweight& fw2 = factory->getFlyweight(s2);
    Context c2(fw2,u2);
    c2.operation();

    Flyweight& fw3 = factory->getFlyweight(s3);
    Context c3(fw3,u3);
    c3.operation();

}

int main(int __argc, char* __argv[]){
    clientCode();
    return 0;
}
