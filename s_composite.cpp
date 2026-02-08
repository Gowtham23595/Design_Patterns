#include <iostream>
#include <memory>
#include <list>
#include <string>
// ...existing code...

using namespace std;

class Component :  public enable_shared_from_this<Component>{
    protected:
    weak_ptr<Component> parent;
    public:
    virtual string Operation() = 0;
    void setParent(const shared_ptr<Component> &s){
        this->parent = s;
    }
};

class Leaf : public Component{
    public:
    string child;
    Leaf(string s) : child(s){}
    string Operation() override{
        return child;
    }
};

class Composite : public Component{
    protected:
    list<shared_ptr<Component>> children;
    public:
    void Add(const shared_ptr<Component> &s){
        children.push_back(s);
        s->setParent(shared_from_this());
    }

    void Remove(const shared_ptr<Component> &s){
        children.remove(s);
        s->setParent(nullptr);
    }

    string Operation() override{
        string result;
        for (auto &c : children){
            result += c->Operation();
        }
        return "Branch( " + result + " )";
    }
};

void ClientCode(const shared_ptr<Component> &component){
    cout << component->Operation();
}

int main(int argc, char* argv[]){
    shared_ptr<Composite> tree = make_shared<Composite>();
    shared_ptr<Leaf> leaf1 = make_shared<Leaf>("leaf1");
    shared_ptr<Leaf> leaf2 = make_shared<Leaf>("leaf2");

    shared_ptr<Composite> Branch1 = make_shared<Composite>();
    shared_ptr<Composite> Branch2 = make_shared<Composite>();

    shared_ptr<Leaf> leaf3 = make_shared<Leaf>("leaf3");
    shared_ptr<Leaf> leaf4 = make_shared<Leaf>("leaf4");

    Branch1->Add(leaf1);
    Branch1->Add(leaf2);
    Branch2->Add(leaf3);
    Branch2->Add(leaf4);
    tree->Add(Branch1);
    tree->Add(Branch2);

    ClientCode(tree);

}