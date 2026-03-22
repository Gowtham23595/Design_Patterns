#include<iostream>
#include<memory>

using namespace std;

struct Node{
    int data;
    shared_ptr<Node> next;
    Node(int val): data(val),next(nullptr){}
};

class LinkedList{
    shared_ptr<Node> head;
    shared_ptr<Node> tail;
    public:
    void insert(int val){
        shared_ptr<Node> newNode = make_shared<Node>(val);
        if(head == nullptr){
            head = newNode;
            tail = newNode;
        }else{
            tail->next = newNode;
            tail = newNode;
        }
    }

    void printList(){
        shared_ptr<Node> node = head;
        while(node != nullptr){
            cout << node->data << " ";
            node = node->next;
        }
        cout << "\n";
    }

    bool search(int val){
        shared_ptr<Node> searchNode = head;
        while(searchNode != nullptr){
            if(searchNode->data != val){
                searchNode = searchNode->next;
            }
            else{
                return true;
            }
        }
    if (searchNode == nullptr){
            return false;
    }
    return false;
    }

    bool remove(int val){
        if(head == nullptr){
            return false;
        }
        shared_ptr<Node> n = head;
        if(n->data == val){
            if(head == tail){
                head = nullptr;
                tail = nullptr;
            }
            else{
                head = head->next;
            }
            return true;
        }
        while(n->next != nullptr && n->next->data != val){
            n = n->next;
        }
        cout << n->data <<"\n";
        if(n->next != nullptr){
            if(n->next == tail){
                n->next = nullptr;
                tail = n;
            }
            else{
                n->next = n->next->next;
            }
            return true;
        }
        return false;
    }

    void traverse(){
        shared_ptr<Node> n = head;
        while(n != nullptr){
            cout << n->data << ",";
            n = n->next;
        }
        cout << "\n";
    }

    void reverseTraverse(){
        shared_ptr<Node> curr = tail;
        if(curr != nullptr){
            while(curr != head){
                shared_ptr<Node> prev = head;
                while(prev->next != curr){
                    prev = prev->next;
                }
                cout << curr->data<<",";
                curr = prev;
            }
            cout << curr->data<<",";
        }
        cout << "\n"; 
    }

};

struct NodeDL
{
    int data;
    shared_ptr<NodeDL> prev;
    shared_ptr<NodeDL> next;
    NodeDL(int val): data(val),prev(nullptr),next(nullptr){}
};


class DoubleLinkedList{
    shared_ptr<NodeDL> head;
    shared_ptr<NodeDL> tail;
    public:
    void Insert(int val){
        shared_ptr<NodeDL> n = make_shared<NodeDL>(val);
        if(head == nullptr){
            head = n;
            tail = head;
        }
        else{
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
    }

    bool remove(int val){
        if(head != nullptr){
            shared_ptr<NodeDL> n = head;
            if(n->data == val){
                n = n->next;
                n->prev = nullptr;
                head = n;
                return true;
            }
            else{
                while(n->next != nullptr && n->next->data != val){
                    n = n->next;
                }
                if(n->next != nullptr){
                    if(n->next == tail){
                        n->next = nullptr;
                        tail = n;
                    }
                    else{
                        n->next = n->next->next;
                        n->next->prev = n;
                    }
                    return true;
                }
            }
        }
        return false;
    }
    void printList(){
        shared_ptr<NodeDL> node = head;
        while(node != nullptr){
            cout << node->data << " ";
            node = node->next;
        }
        cout << "\n";
    }

    void reverseTraverse(){
        shared_ptr<NodeDL> node = tail;
        while (node != nullptr)
        {
            cout << node->data << ",";
            node = node->prev;
        }
        cout << "\n";
    }

};


void clientCode(){
    LinkedList ln;
    ln.insert(20);
    ln.insert(30);
    ln.printList();
    ln.insert(40);
    ln.insert(50);
    ln.printList();
    cout << ln.remove(100) << "\n";\
    ln.printList();
    ln.traverse();
    ln.reverseTraverse();

    DoubleLinkedList dLn;
    dLn.Insert(200);
    dLn.Insert(300);
    dLn.Insert(400);
    dLn.Insert(500);
    dLn.printList();
    dLn.remove(400);
    dLn.printList();
    dLn.reverseTraverse();


}

int main(){
    clientCode();
    return 0;
}