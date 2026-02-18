#include <iostream>
#include "BinarySearchTree.hpp"
#include "BinaryTreeNode.hpp"

int main()
{
    BinarySearchTree<int> bst = BinarySearchTree<int>();

    int data[7] = {1, 7, 3, 10, 8, 4, 5};

    for (int i = 0; i < 7; i++)
    {
        cout << "트리에 " << data[i] << "삽입: ";
        bst.insert_data(data[i]);
        cout << "\n";
    }
    cout << "\n";

    
    cout << "트리에 6이 존재합니까? : " << bst.search_data(6) << "\n";
    cout << "트리에 7이 존재합니까? : " << bst.search_data(7) << "\n";
    cout << "트리에 9이 존재합니까? : " << bst.search_data(9) << "\n";

    cout << "\n트리에서 7 삭제 : ";
    bst.delete_data(7);
    cout << "\n트리에서 1 삭제 : ";
    bst.delete_data(1);
    cout << "\n트리에서 5 삭제 : ";
    bst.delete_data(5);
}