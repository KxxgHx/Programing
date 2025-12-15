#pragma once

#include <iostream>
#include "BinaryTreeNode.hpp"
using namespace std;

template <typename T>
class BinarySearchTree {
private:
    BinaryTreeNode<T>* root_ptr;

    BinaryTreeNode<T>* insert_node(BinaryTreeNode<T>* node, T data) {
        if (node == nullptr)
            return new BinaryTreeNode<T>(data);

        if (data <= node->data())
            node->set_left(insert_node(node->left(), data));
        else if (data > node->data())
            node->set_right(insert_node(node->right(), data));

        return node;
    }

    BinaryTreeNode<T>* search_node(BinaryTreeNode<T>* node, T data) {
        if (node == nullptr || node->data() == data)
            return node;

        if (data < node->data())
            return search_node(node->left(), data);
        else
            return search_node(node->right(), data);
    }

    BinaryTreeNode<T>* find_max(BinaryTreeNode<T>* node) {
        while (node && node->right() != nullptr)
            node = node->right();
        return node;
    }

    BinaryTreeNode<T>* delete_node(BinaryTreeNode<T>* node, T data) {
        if (node == nullptr) return node;

        if (data < node->data())
            node->set_left(delete_node(node->left(), data));
        else if (data > node->data())
            node->set_right(delete_node(node->right(), data));
        else {
            if (node->left() == nullptr) {
                BinaryTreeNode<T>* right = node->right();
                delete node;
                return right;
            }
            else {
                BinaryTreeNode<T>* sub_max = find_max(node->left());
                node->set_data(sub_max->data());
                node->set_left(delete_node(node->left(), sub_max->data()));
            }
        }
        return node;
    }

    void BST_inorder_print(BinaryTreeNode<T>* root_ptr) {
        if (root_ptr != nullptr) {
            BST_inorder_print(root_ptr->left());
            cout << root_ptr->data() << " ";
            BST_inorder_print(root_ptr->right());
        }
    }

public:
    BinarySearchTree(BinaryTreeNode<T>* init_root = nullptr) {
        root_ptr = init_root;
    }

    void insert_data(T data) {
        root_ptr = insert_node(root_ptr, data);
        BST_inorder_print(root_ptr);
    }

    bool search_data(T data) {
        return search_node(root_ptr, data) != nullptr;
    }

    void delete_data(T data) {
        root_ptr = delete_node(root_ptr, data);
        BST_inorder_print(root_ptr);
    }
};
