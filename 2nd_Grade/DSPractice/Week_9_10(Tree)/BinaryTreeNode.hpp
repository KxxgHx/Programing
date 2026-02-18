#pragma once

#include <iostream>
using namespace std;

template <typename T>
class BinaryTreeNode {
private:
    T data_field;
    BinaryTreeNode* left_field;   // 왼쪽 자식 노드
    BinaryTreeNode* right_field;  // 오른쪽 자식 노드

public:
    BinaryTreeNode(const T& init_data,
                   BinaryTreeNode* init_left = nullptr,
                   BinaryTreeNode* init_right = nullptr)
    {
        data_field = init_data;
        left_field = init_left;
        right_field = init_right;
    }

    T& data() { return data_field; }
    BinaryTreeNode*& left() { return left_field; }
    BinaryTreeNode*& right() { return right_field; }

    void set_data(const T& new_data) { data_field = new_data; }
    void set_left(BinaryTreeNode* new_left) { left_field = new_left; }
    void set_right(BinaryTreeNode* new_right) { right_field = new_right; }

    bool is_leaf() { return left_field == nullptr && right_field == nullptr; }
};

//--------------------------------------------
// 자식 출력 함수
//--------------------------------------------
template <typename T>
void print_children(BinaryTreeNode<T>* node_ptr) {
    if (node_ptr == nullptr) return;

    cout << node_ptr->data() << "의 자식: ";
    if (node_ptr->left() != nullptr)
        cout << node_ptr->left()->data() << " ";
    if (node_ptr->right() != nullptr)
        cout << node_ptr->right()->data() << " ";
    cout << endl;

    if (!node_ptr->is_leaf()) {
        print_children(node_ptr->left());
        print_children(node_ptr->right());
    }
}

//--------------------------------------------
// 전위 순회
//--------------------------------------------
template <typename T>
void preorder_print(BinaryTreeNode<T>* root_ptr) {
    if (root_ptr != nullptr) {
        cout << root_ptr->data() << " ";
        preorder_print(root_ptr->left());
        preorder_print(root_ptr->right());
    }
}

//--------------------------------------------
// 중위 순회
//--------------------------------------------
template <typename T>
void inorder_print(BinaryTreeNode<T>* root_ptr) {
    if (root_ptr != nullptr) {
        inorder_print(root_ptr->left());
        cout << root_ptr->data() << " ";
        inorder_print(root_ptr->right());
    }
}

//--------------------------------------------
// 후위 순회
//--------------------------------------------
template <typename T>
void postorder_print(BinaryTreeNode<T>* root_ptr) {
    if (root_ptr != nullptr) {
        postorder_print(root_ptr->left());
        postorder_print(root_ptr->right());
        cout << root_ptr->data() << " ";
    }
}
