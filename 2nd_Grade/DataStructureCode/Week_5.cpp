#include <iostream>
#include "SingleList.h"
//#include "SingleList_practice.h"

using namespace std;

int main()
{
    singleList list;
    HeadNode* L;
    L = list.createList();

    cout << "1. 빈 연결 리스트를 생성" << endl << endl;

    int data1, data2, data3;
    cout << "2. 연결 리스트에 추가할 노드의 데이터를 3개 입력: ";
    cin >> data1 >> data2 >> data3;
    list.addNode(L, data1);
    list.printList(L);
    list.addNode(L, data2);
    list.printList(L);
    list.addNode(L, data3);
    list.printList(L);
    cout << endl;

    cout << "3. 탐색할 노드의 데이터: ";
    int data4;
    cin >> data4;
    list.searchNode(L, data4);
    cout << endl;

    cout << "4-1. 데이터를 추가할 노드 선택: ";
    int data5, data6;
    cin >> data5;
    cout << "4-2. 추가하고 싶은 값 입력: ";
    cin >> data6;
    list.addThisNode(L, data5, data6);
    list.printList(L);
    cout << endl;

    cout << "5. 삭제하고자 하는 노드 입력: ";
    int data7;
    cin >> data7;
    list.deleteThisNode(L, data7);
    list.printList(L);
    cout << endl;

    // 데이터 삭제할 때 Head 및 Tail 노드는 삭제하면 오류가 발생함
    cout << "6. 마지막 노드 삭제" << endl;
    list.deleteNode(L);
    list.printList(L);
    cout << endl;
}