#include <iostream>

#include "BinaryTreeNode.hpp"
#include "BinarySearchTree.hpp"

using namespace std;

int main()
{
    BinaryTreeNode<char> root = BinaryTreeNode<char>('A');
    BinaryTreeNode<char> node1 = BinaryTreeNode<char>('B');
    BinaryTreeNode<char> node2 = BinaryTreeNode<char>('C');
    BinaryTreeNode<char> node3 = BinaryTreeNode<char>('D');
    BinaryTreeNode<char> node4 = BinaryTreeNode<char>('E');
    BinaryTreeNode<char> node5 = BinaryTreeNode<char>('F');
    BinaryTreeNode<char> node6 = BinaryTreeNode<char>('G');

    root.set_left(&node1);
    root.set_right(&node2);
    node1.set_left(&node3);
    node1.set_right(&node4);
    node2.set_left(&node5);
    node3.set_left(&node6);

    print_children(&root);

    
}