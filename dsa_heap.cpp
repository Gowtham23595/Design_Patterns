#include <iostream>
#include <memory>

using namespace std;

template <typename T, std::size_t N>
class Heap{
    std::array<T,N> heap{-1};
    int count{};
public:
    void insert(T val){
        heap[count] = val;
        count = count + 1;
        minHeap();
    }
    void minHeap(){
        int i = count - 1;
        while(i > 0 && heap[i] < heap[(i-1)/2]){
            std::swap(heap[i],heap[(i-1)/2]);
            i = (i-1)/2;
        }
    }

    void print(){
        for(int i = 0; i < heap.size(); i++){
            cout << heap[i] << ",";
        }
        cout << "\n";
    }

    void remove(T val){
        int index = findIndex(val);
        if(index == -1){
            cout << "Element Not found\n";
            return;
        }
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        count = count - 1;
        heap[index] = heap[count]; 
        heap[count] = 0;
        while(left < count && (heap[left] < heap[index] || heap[right] < heap[index])){
            if(heap[left] < heap[right]){
                std::swap(heap[left],heap[index]);
                index = left;
            }
            else{
                std::swap(heap[right], heap[index]);
                index = right;
            }
             
        }
    }

    int findIndex(T val){
        for(int i = 0; i < heap.size(); i++){
            if(heap[i] == val){
                return i;
            }
        }
        return -1;
    }

};

void clientCode(){
    shared_ptr<Heap<int,10>> pH = make_shared<Heap<int,10>>();
    pH->insert(3);
    pH->insert(9);
    pH->insert(7);
    pH->insert(12);
    pH->insert(1);
    pH->print();
    pH->remove(7);
    pH->print();
}

int main(){
    clientCode();
    return 0;
}