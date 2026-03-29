#include<iostream>

using namespace std;

template<typename T>
class Sample{
    private:
    T data;

    public:
    Sample(T val) : data(val){
        cout <<"Param ctor\n";
    }
    ~Sample()=default;
    Sample(const Sample &other){
        cout <<"Copy ctor\n";
        this->data = other.data;
    }
    Sample& operator=(const Sample &other){
        cout <<"Copy assign\n";

        if(this != &other){
            this->data = other.data;
        }
        return *this;
    }

    Sample(Sample &&other){
        cout <<"Move ctor\n";
        this->data = std::move(other.data);
    }

    Sample& operator=(Sample &&other){
        cout <<"Move assign\n";
        if(this != &other){
            this->data = std::move(other.data);
        }
        return *this;
    }
    void print(){
        cout << data << "\n";
    }
    void setData(T val){
        this->data = val;
    }
};

int main(){
    Sample<string> obj("Hi");
    obj.print();
    Sample<string> obj2(obj);
    obj2.print();
    Sample<string> obj3("");
    obj3.print();
    obj2.setData("Hello");
    obj3 = obj2;
    obj3.print();
    Sample<string> obj4(std::move(obj3));
    obj3.print();
    obj4.print();

}