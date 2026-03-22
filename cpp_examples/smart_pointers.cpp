#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Employee;

class Department{
    public:
    string name;
    Department(string val){
        name = val;
    }
    ~Department(){
        cout << "Department Dtor\n";
    }
};

class Company{
    public:
    string name;
    vector<shared_ptr<Employee>> pEmp;
    vector<unique_ptr<Department>> pDpt;
    Company(string val){
        this->name = val; 
    }
    ~Company(){
        cout << "Company Dtor\n";
    };
    void addEmp(shared_ptr<Employee> &e){
        pEmp.push_back(e);
        
    }
    void addDept(unique_ptr<Department> d){
        pDpt.push_back(std::move(d));
    }
    void printRecords();

};

class Employee{
    public:
    string name{};
    weak_ptr<Company> pCmp;
    Employee(string val,shared_ptr<Company> p){
        name = val;
        pCmp = p;
    }
    ~Employee(){
        cout << "Employee dtor\n";
    }
    void accessCompanyName(){
        auto cmp = pCmp.lock();
        if(cmp){
        cout << "Company name :"<<cmp->name <<"\n";
        }
        else
        {
            cout << "Company name deleted\n";
        }
    }
};

void Company::printRecords(){
    for (const auto& emp : pEmp) {
        cout << emp->name << "\n";
    }
}

int main(int argc, char* argv[]){
    auto d1 = make_unique<Department>("HR");
    auto d2 = std::move(d1);
    if(!d1){
        cout << "pointer is moved\n";
    }
    auto c = make_shared<Company>("Infosys");
    auto e1 = make_shared<Employee>("John",c);
    c->addEmp(e1);
    c->addDept(std::move(d2));
    c->printRecords();
    e1->accessCompanyName();
    c.reset();
    e1->accessCompanyName();
}
