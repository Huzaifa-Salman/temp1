#include <iostream>
#include <vector>
using namespace std;

class Heap{
    public:
        vector<int> array;
        void insertMax(int val); // maxHeap
        void insertMin(int val); // minHeap
        void display();
        void delMin();
        void delMax();
        
        // -------------------------
        void printSmallerThan(int x);
        void printSmallerThan(int x, int index);
};

int main(){
    Heap heap;
    heap.insertMax(55);
    heap.insertMax(10);
    heap.insertMax(30);
    heap.insertMax(88);
    heap.insertMax(2);
    heap.insertMax(34);
    heap.display();
    cout << "Deleting root: ";
    heap.delMax();
    cout << "heap: ";
    heap.display();

    cout << " --------------------------- " << endl;
    Heap heap2;
    heap2.insertMin(2);
    heap2.insertMin(3);
    heap2.insertMin(15);
    heap2.insertMin(5);
    heap2.insertMin(4);
    heap2.insertMin(45);
    heap2.insertMin(80);
    heap2.insertMin(6);
    heap2.insertMin(180);
    heap2.insertMin(77);
    heap2.insertMin(120);
    heap2.display();
    cout << "Less than 80: ";
    heap2.printSmallerThan(80);

    return 0;
}

void Heap::insertMax(int val){
    if(0 == array.size()){
        array.push_back(val);
    }
    else{
        array.push_back(val);
        int index = array.size() - 1;
        while(index > 0){
            int parent = (index-1)/2;
            if(array[parent] < array[index]){
                swap(array[parent], array[index]);
                index = parent;
            }
            else{
                break;
            }
        }
    }
}
void Heap::insertMin(int val){
    if(0 == array.size()){
        array.push_back(val);
    }
    else{
        array.push_back(val);
        int index = array.size() - 1;
        while(index > 0){
            int parent = (index-1)/2;
            if(array[parent] >= array[index]){
                swap(array[parent], array[index]);
                index = parent;
            }
            else{
                break;
            }
        }
    }
}
void Heap::delMax(){
    if(0 == array.size()){
        return;
    }
    else{
        int n = array.size();
        array[0] = array[n-1];
        array.pop_back();
        n = array.size(); // size is changed

        int index = 0;
        while(index < n){
            int left = 2*index + 1;
            int right = 2*index + 2;

            if(left < n && array[index] < array[left]){
                swap(array[index], array[left]);
                index = left;
            }
            else if(right < n && array[index] < array[right]){
                swap(array[index], array[right]);
                index = right;
            }
            else{
                return;
            }
        }

    }
}
void Heap::display(){
    if(0 == array.size()){
        cout << "Error: Nothing to display!" << endl;
    }
    else{
        for(int i: array){
            cout << i << " ";
        } cout << endl;
    }
}

void Heap::printSmallerThan(int x){
    printSmallerThan(x, 0);
}
void Heap::printSmallerThan(int x, int index){
    int n = array.size();
    // cases
    if(index >= n){
        return;
    }
    if(array[index] >= x){
        return;
    }
    cout << array[index] << " ";
    printSmallerThan(x, 2*index + 1); // call for left child
    printSmallerThan(x, 2*index + 2); // call for right child
}