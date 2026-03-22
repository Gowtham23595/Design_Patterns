#include<iostream>
#include<memory>
#include <queue>

using namespace std;

template<typename T>
struct Node{
    T data;
    shared_ptr<Node> left;
    shared_ptr<Node> right;
    Node(T val): data(val), left(nullptr),right(nullptr){}
};
template<typename T>
class BinarySearchTree{
    shared_ptr<Node<T>> root;
    int count{};
    public:
    void insert(T val){
        if(root == nullptr){
            root = make_shared<Node<T>>(val);
            count++;
        }
        else{
            insertNode(root,val);
        }
    }
    void insertNode(shared_ptr<Node<T>> root_,T val){
        shared_ptr<Node<T>> n = root_;
        if(val < n->data){
            if(n->left == nullptr){
                n->left = make_shared<Node<T>>(val);
                count++;

            }
            else{
                insertNode(n->left,val);
            }
        }
        else{
            if(n->right == nullptr){
                n->right = make_shared<Node<T>>(val);
                count++;
            }
            else{
                insertNode(n->right,val);
            }
        }
    }
    bool search(T val){
        if(root == nullptr){
            return false;
        }
        else
        {
            if(root->data == val){
                cout << "In root :" << val<<"\n";
                return true;
            }
            else if(val < root->data){
                if(root->left != nullptr){
                    return contains(root->left,val);
                }
            }
            else{
                if(root->right != nullptr){
                return contains(root->right,val);
                }
            }
            return false;
        }
    }

    bool contains(shared_ptr<Node<T>> root_, T val){
        if(root_ != nullptr){
            if(root_->data == val){
                return true;
            }
            else if(val < root_->data){
                return contains(root_->left,val);
            }
            else{
                return contains(root_->right,val);
            }
        }
        return false;
    }

    shared_ptr<Node<T>> FindNode(shared_ptr<Node<T>> root_,T val){
        if(root_ != nullptr){
            cout << root_->data << "," <<val<< "\n";
            if(root_->data == val){
                return root_;
            }
            if(root_->data > val){
                return FindNode(root_->left,val);
            }
            else{
                return FindNode(root_->right,val);
            }
        }
        return nullptr;
    }
    shared_ptr<Node<T>> FindParent(shared_ptr<Node<T>> root_,T val){
        if(root_ != nullptr){
            cout << "Finding Parent :"<<root_->data <<"\n";
            if (root_->data == val){
                return nullptr;
            }
            if(val < root_->data){
                if(root_->left == nullptr){
                    return nullptr;
                }
                else if(root_->left->data == val){
                    return root_;
                }
                else{
                    return FindParent(root_->left,val);
                }
            }
            else{
                if(root->right == nullptr){
                    return nullptr;
                }
                else if(root_->right->data == val){
                    return root_;
                }
                else{
                    return FindParent(root_->right,val);
                }
            }
        }
        return nullptr;
    }

    bool remove(T val){
      if(root == nullptr){
        return false;
      }  
      if(count == 1){
        root = nullptr;
        return true;
      }
      shared_ptr<Node<T>> nodeToRemove = FindNode(root,val);
      if(nodeToRemove == nullptr){
        cout << "value not found\n";
        return false;
      }
      shared_ptr<Node<T>> parent = FindParent(root,val);
      if(parent != nullptr)
      {
        if(nodeToRemove->left == nullptr && nodeToRemove->right == nullptr){
            if(nodeToRemove->data < parent->data ){
                parent->left = nullptr;
            }
            else{
                parent->right = nullptr;
            }
        }
        else if(nodeToRemove->left != nullptr && nodeToRemove->right == nullptr){
            if(nodeToRemove->data < parent->data ){
                parent->left = nodeToRemove->left;
            }
            else{
                parent->right = nodeToRemove->left;
            }
        }
        else if(nodeToRemove->left == nullptr && nodeToRemove->right != nullptr){
            if(nodeToRemove->data < parent->data ){
                parent->left = nodeToRemove->right;
            }
            else{
                parent->right = nodeToRemove->right;
            }
        }
        else{
            cout << "two leaf nodes :" << parent->data << "," << nodeToRemove->data <<"\n";
            shared_ptr<Node<T>> largestNode = nodeToRemove->right;
            while(largestNode->right != nullptr){
                largestNode = largestNode->right;
            }
            FindParent(root,largestNode->data)->right = nullptr;
            nodeToRemove->data = largestNode->data;
        }
      }
      count = count - 1;
      return true;
    }
    void print(bool flag){
        if(flag == true){
            preorder(root);
        }
        else{
            //postorder(root);
            inorder(root);
        }
        cout << count;
    }

    void preorder(shared_ptr<Node<T>> root_){
        if(root_ != nullptr){
            cout << root_->data << ",";
            preorder(root_->left);
            preorder(root_->right);
        }
    }
    void postorder(shared_ptr<Node<T>> root_){
        if(root_ != nullptr){
            postorder(root_->left);
            postorder(root_->right);
            cout << root_->data << ",";
        }
    }
    void inorder(shared_ptr<Node<T>> root_){
        if(root_ != nullptr){
            inorder(root_->left);
            cout << root_->data << ",";
            inorder(root_->right);
        }
    }

    void breadthfirst(){
        queue<shared_ptr<Node<T>>> q;
        shared_ptr<Node<T>>root_ = root;
        while(root_ != nullptr){
            cout << root_->data<<",";
            if(root_->left != nullptr){
                q.push(root_->left);
            }
            if(root_->right != nullptr){
                q.push(root_->right);
            }
            if(!q.empty()){
                root_ = q.front();
                q.pop();
            }
            else{
                cout << "else";
                root_ = nullptr;
            }
        }
    }

};

void clientCode(){
    shared_ptr<BinarySearchTree<int>> b = make_shared<BinarySearchTree<int>>();
    b->insert(23);
    b->insert(14);
    b->insert(7);
    b->insert(17);
    b->insert(9);
    b->insert(31);
    cout << b->search(50)<<"\n";

    b->print(true);
    cout <<"\n";
    b->print(false);
    cout <<"\n";
    //b->remove(14);
    //b->print(false);
    cout <<"\n";
    b->breadthfirst();


}

int main(){
    clientCode();
    return 0;
}