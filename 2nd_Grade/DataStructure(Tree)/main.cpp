#include "binary_tree_node.h" 
#include "bag.h"              
#include <iostream>
#include <string>

using namespace BST;
using namespace std;

void print_indentation(int depth) //들여쓰기 공백 문자 출력 함수
{
    const int Space_Per_Level = 4;
    for (int i = 0; i < depth * Space_Per_Level; ++i)
    {
        cout << ' ';
    }
}

template <class Item>
void print_tree_structure(const binary_tree_node<Item> *root_ptr, int depth)
{
    if(root_ptr != NULL)
    {
        print_tree_structure(root_ptr->right(), depth + 1); //right subtree(recursive call)

        print_indentation(depth); //print root
        cout << root_ptr->data() << endl;

        print_tree_structure(root_ptr->left(), depth + 1); //left subtree (recursive call)
    }
}

int main()
{
    cout << "-----Binary Search Tree TEST-----" << endl;

    bag<int> int_bag;
    cout << "초기 Bag 크기 : " << int_bag.size() << endl;

    cout << "\n데이터 삽입 (17, 8, 22, 3, 13, 19, 65, 10, 1, 5, 22): " << endl;
    int_bag.insert(17);
    int_bag.insert(8);
    int_bag.insert(22);
    int_bag.insert(3);
    int_bag.insert(13);
    int_bag.insert(19);
    int_bag.insert(65);
    int_bag.insert(10);
    int_bag.insert(1);
    int_bag.insert(5);
    int_bag.insert(22);

    cout << "삽입 후의 Bag 크기 : " << int_bag.size() << endl;

    cout << "\n [Binary Search Tree 구조(90도 회전)]" << endl;
    
    print_tree_structure(int_bag.get_root(), 0);

    cout << "---요소 삭제 TEST---" << endl;

    if (int_bag.erase_one(1)) {
        cout << "성공: 1을 삭제했습니다. 현재 크기: " << int_bag.size() << endl;
    } 

    cout << "\n루트 노드 17 삭제 시도 (13이 대체 예상)..." << endl;
    if (int_bag.erase_one(17)) {
        cout << "성공: 17을 삭제했습니다. 현재 크기: " << int_bag.size() << endl;
    } 

    cout << "\n[BST 구조 (17 삭제 후, 새로운 루트는 13)]" << endl;
    print_tree_structure(int_bag.get_root(), 0); 

    cout << "\n--- 복사 및 연산자 테스트 ---" << endl;

    // 복사 생성자 테스트
    bag<int> bag_copy = int_bag; 
    cout << "bag_copy 생성. 크기: " << bag_copy.size() << endl;

    // += 연산자 테스트
    cout << "\nint_bag += bag_copy (Self-addition) 테스트" << endl;
    int_bag += bag_copy;
    cout << "int_bag 크기 (삭제 전의 2배여야 함): " << int_bag.size() << endl;
}