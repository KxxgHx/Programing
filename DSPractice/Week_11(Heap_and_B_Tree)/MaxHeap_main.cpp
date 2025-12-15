#include "MaxHeap.hpp"

int main() {
    MaxHeap<int> mh = MaxHeap<int>();
    int data[6] = { 7, 3, 9, 5, 10, 4 };

    for (int i = 0; i < 6; i++) {
        cout << "힙에 " << data[i] << " 추가: ";
        mh.push(data[i]);
        mh.print_heap();
    }
    cout << endl;

    while (mh.size() > 0) {
        cout << "힙에서 최댓값 제거: " << mh.pop() << endl;
        cout << "힙 상태: ";
        mh.print_heap();
    }

    return 0;
}