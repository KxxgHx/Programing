#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
class MinHeap {
private:
    vector<T> heap;

    void downward_reheapificate(int index) {
        if (index == 1) {
            return;
        }

        int parent = index / 2;

        if (heap[index] < heap[parent]) {
            T temp = heap[index];
            heap[index] = heap[parent];
            heap[parent] = temp;
            
            downward_reheapificate(parent);
        }
        return;
    }

    void upward_reheapificate(int index) {
        int left_child = 2 * index;
        int right_child = 2 * index + 1;
        int smaller_child;

        if (left_child > heap.size() - 1) {
            return;
        }
        else if (right_child > heap.size() - 1) {
            smaller_child = left_child;
        }
        else {
            smaller_child = (heap[left_child] < heap[right_child]) ? left_child : right_child;
        }

        if (heap[index] < heap[smaller_child]) {
            T temp = heap[index];
            heap[index] = heap[smaller_child];
            heap[smaller_child] = temp;

            upward_reheapificate(smaller_child);
        }
        
        return;
    }

public:
    MinHeap() {
        heap.push_back(T()); 
    }

    void push(T data) {
        heap.push_back(data);
        downward_reheapificate(heap.size() - 1);
    }

    T pop() {
        if (heap.size() == 1) { 
            return NULL;
        }

        T pop_data = heap[1];
        heap[1] = heap[heap.size() - 1];
        heap.pop_back();

        upward_reheapificate(1);

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