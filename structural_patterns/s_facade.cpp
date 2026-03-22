 #include <iostream>
 #include <memory>

 using namespace std;

class Subsystem1{
    public:
    string operation(){
        return "System 1";
    }
};

class Subsystem2{
    public:
    string operation(){
        return "System 2";
    }
};

class Facade{
    protected:
    shared_ptr<Subsystem1> pSys1;
    shared_ptr<Subsystem2> pSys2;
    public:
    Facade(shared_ptr<Subsystem1> s1, shared_ptr<Subsystem2> s2): pSys1(s1),pSys2(s2){}
    string operation(){
        return pSys1->operation() + " " + pSys2->operation();
    }
};

void ClientCode(const shared_ptr<Facade> &fObj){
    cout << fObj->operation();
}

int main(){
    shared_ptr<Subsystem1> s1 = make_shared<Subsystem1>();
    shared_ptr<Subsystem2> s2 = make_shared<Subsystem2>();
    shared_ptr<Facade> fObj = make_shared<Facade>(s1,s2);
    ClientCode(fObj);
}