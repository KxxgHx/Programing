#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
class MaxHeap {
private:
    vector<T> heap;

    void upward_reheapificate(int index) {
        if (index == 1) {
            return;
        }

        int parent = index / 2;

        if (heap[index] > heap[parent]) {
            T temp = heap[index];
            heap[index] = heap[parent];
            heap[parent] = temp;
            
            upward_reheapificate(parent);
        }
        return;
    }

    void downward_reheapificate(int index) {
        int left_child = 2 * index;
        int right_child = 2 * index + 1;
        int larger_child;

        if (left_child > heap.size() - 1) {
            return;
        }
        else if (right_child > heap.size() - 1) {
            larger_child = left_child;
        }
        else {
            larger_child = (heap[left_child] > heap[right_child]) ? left_child : right_child;
        }

        if (heap[index] < heap[larger_child]) {
            T temp = heap[index];
            heap[index] = heap[larger_child];
            heap[larger_child] = temp;

            downward_reheapificate(larger_child);
        }
        
        return;
    }

public:
    MaxHeap() {
        heap.push_back(T()); 
    }

    void push(T data) {
        heap.push_back(data);
        upward_reheapificate(heap.size() - 1);
    }

    T pop() {
        if (heap.size() == 1) { 
            return NULL;
        }

        T pop_data = heap[1];
        heap[1] = heap[heap.size() - 1];
        heap.pop_back();

        downward_reheapificate(1);

        return pop_data;
    }

    int size() {
        return heap.size() - 1;
    }
    
    void print_heap() {
        for (int i = 1; i < heap.size(); i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};