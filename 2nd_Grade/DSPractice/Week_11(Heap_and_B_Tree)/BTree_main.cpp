#include "BTree.hpp"

int main() {
    BTree<int> bt = BTree<int>(3); 

    cout << "트리에 10, 15, 20 추가" << endl;
    bt.insert(10);
    bt.insert(15);
    bt.insert(20);
    bt.print_tree();

    cout << endl << "트리에 30 추가" << endl;
    bt.insert(30);
    bt.print_tree();

    cout << endl << "트리에 40 추가" << endl;
    bt.insert(40);
    bt.print_tree();

    cout << endl << "트리에 8 추가" << endl;
    bt.insert(8);
    bt.print_tree();

    cout << endl << "트리에 5 추가" << endl;
    bt.insert(5);
    bt.print_tree();
    
    cout << endl << "트리에 20이 존재하는가?: " << (bt.search(20) ? "Yes" : "No") << endl;
    cout << "트리에 50이 존재하는가?: " << (bt.search(50) ? "Yes" : "No") << endl;

    return 0;
}