#include <iostream>

using namespace std;

struct Node {
    char left;
    char right;
};

Node tree[27];

void preOrder(char node) {
    if (node == '.') return;
    
    cout << node;                 
    preOrder(tree[node - 'A'].left);
    preOrder(tree[node - 'A'].right);
}

void inOrder(char node) {
    if (node == '.') return;

    inOrder(tree[node - 'A'].left);
    cout << node;      
    inOrder(tree[node - 'A'].right);
}

void postOrder(char node) {
    if (node == '.') return;

    postOrder(tree[node - 'A'].left);
    postOrder(tree[node - 'A'].right);
    cout << node;                 
}

int main() {
    int N;
    cin >> N;

    char root, l, r;
    for (int i = 0; i < N; i++) {
        cin >> root >> l >> r;
        tree[root - 'A'].left = l;
        tree[root - 'A'].right = r;
    }

    preOrder('A');
    cout << "\n";
    
    inOrder('A');
    cout << "\n";
    
    postOrder('A');
    cout << "\n";

    return 0;
}