#include <iostream>
#include <memory>

using namespace std;

template<typename T>
class foo{
    private:
    T data;

    public:
    foo(T val){
        data = val;
    }
    ~foo(){
        cout << "dTor called "<< data << "\n";
    };

    foo(const foo &other){
        cout << "copy ctor\n";
        this->data = other.data;
    }
    foo& operator=(const foo &other){
        cout << "Copy assignment\n";
        if(this != &other){
        this->data = other.data;
        }
        return *this;
    }

    foo(foo &&other){
        cout << "Move ctor\n";
        data = std::move(other.data);
    }
    foo& operator=(foo &&other){
        cout << "Move assignment\n";
        data = std::move(other.data); 
        return *this;
    }
    void print(){
        cout << this->data<<"\n";
    }
    void set(T val){
        this->data = val;
    }

};

int main(int argc, char* argv[]){
    foo<int> obj1(10);
    obj1.print();
    foo<int> obj2(obj1);
    obj2.print();
    obj2.set(30);
    foo<int> obj3(std::move(obj2));
    obj3.print();
    obj2.print();
    foo<int> obj4(20);
    obj4 = std::move(obj3);
    foo<int> obj5(50);
    obj5 = obj2;
    obj4.print();
    obj5.print();

    foo<string> s1("Hi");
    s1.print();
    foo<string> s2("Hello");
    s2.print();
    s2 = std::move(s1);
    s1.print(); 
    return 0;
}