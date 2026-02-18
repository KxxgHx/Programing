#include <iostream>
#include "BinarySearchTree.hpp"
#include "BinaryTreeNode.hpp"

using namespace std;

int main()
{
    BinaryTreeNode<char> root = BinaryTreeNode<char>('*');
    BinaryTreeNode<char> node1 = BinaryTreeNode<char>('+');
    BinaryTreeNode<char> node2 = BinaryTreeNode<char>('-');
    BinaryTreeNode<char> node3 = BinaryTreeNode<char>('3');
    BinaryTreeNode<char> node4 = BinaryTreeNode<char>('y');
    BinaryTreeNode<char> node5 = BinaryTreeNode<char>('2');
    BinaryTreeNode<char> node6 = BinaryTreeNode<char>('x');

    root.set_left(&node1);
    root.set_right(&node2);
    node1.set_left(&node3);
    node1.set_right(&node4);
    node2.set_left(&node5);
    node2.set_right(&node6);

    cout << "전위 순회 : ";
    preorder_print(&root);
    cout << '\n';

    cout << "중위 순회 : ";
    inorder_print(&root);
    cout << '\n';

    cout << "후위 순회 : ";
    postorder_print(&root);
    cout << '\n';
}