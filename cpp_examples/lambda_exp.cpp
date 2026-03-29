#include <iostream>
#include <memory>
#include <vector>

using namespace std;

void print(vector<int> &v){
    for (auto i :v){
        cout << i << " ";
    }
    cout << "\n";
}

int main(){

    vector<int> v1;
    vector<int> v2;

    auto byRef = [&](int a, int b){
        v1.push_back(a);
        v2.push_back(b);
    };

    byRef(10,20);
    print(v1);
    print(v2);

    auto byVal = [&v1,v2](int a, int b)mutable{
        v1.push_back(a);
        v2.push_back(b);
    };
    byVal(100,200);

    print(v1);
    print(v2);



    int a = 5;
    auto f = [a](){ return a + 3; };
    cout << f();
}

