#pragma once
#include <iostream>

using namespace std;

// 노드 구조체 정의
struct Node {
    int data;
    struct Node* link;
};

// 헤드 노드 구조체 정의
struct HeadNode {
    Node* head;
};

// 단일 연결 리스트 클래스
class singleList {
public:
    // 빈 연결 리스트 생성
    HeadNode* createList() {
        HeadNode* H = new HeadNode;
        H->head = NULL;
        return H;
    }

    // 리스트의 마지막에 노드 추가
    void addNode(HeadNode* H, int x) {
        Node* NewNode = new Node;
        Node* LastNode;
        NewNode->data = x;
        NewNode->link = NULL;

        if (H->head == NULL) {
            H->head = NewNode;
            return;
        }

        LastNode = H->head;
        while (LastNode->link != NULL) LastNode = LastNode->link;
        LastNode->link = NewNode;
    }
    
    // 특정 노드 뒤에 새로운 노드 추가
    void addThisNode(HeadNode* H, int afterthisdata, int adddata) {
        Node* prevNode;
        prevNode = H->head;

        while (prevNode->data != afterthisdata) {
            prevNode = prevNode->link;
        }

        Node* NewNode = new Node;
        NewNode->data = adddata;
        NewNode->link = prevNode->link;
        prevNode->link = NewNode;
        return;
    }

    // 특정 데이터 값을 가진 노드 탐색
    void searchNode(HeadNode* H, int thisdata) {
        Node* someNode;
        someNode = H->head;
        while (someNode->data != thisdata) {
            someNode = someNode->link;
        }
        cout << thisdata << " 데이터 검색 성공" << endl;
    }

    // 리스트의 마지막 노드 삭제
    void deleteNode(HeadNode* H) {
        Node* prevNode;
        Node* delNode;

        if (H->head == NULL) return;
        if (H->head->link == NULL) {
            delete H->head;
            H->head = NULL;
            return;
        }
        else {
            prevNode = H->head;
            delNode = H->head->link;
            while (delNode->link != NULL) {
                prevNode = delNode;
                delNode = delNode->link;
            }
            free(delNode);
            prevNode->link = NULL;
        }
    }

    // 특정 데이터 값을 가진 노드 삭제
    void deleteThisNode(HeadNode* H, int deldata) {
        Node* delNode;
        Node* prevNode;
        prevNode = H->head;

        // 삭제할 노드의 이전 노드를 찾음
        while (prevNode->link->data != deldata) {
            prevNode = prevNode->link;
        }

        delNode = prevNode->link;
        prevNode->link = delNode->link;
        free(delNode);
        cout << deldata << " 데이터 값을 가진 노드 삭제" << endl;
        return;
    }

    // 리스트 전체 출력
    void printList(HeadNode* L) {
        Node* p;
        cout << "연결리스트 목록 = ( ";
        p = L->head;
        while (p != NULL) {
            cout << p->data;
            p = p->link;
            if (p != NULL) cout << " --> ";
        }
        cout << " )" << endl;
    }
};