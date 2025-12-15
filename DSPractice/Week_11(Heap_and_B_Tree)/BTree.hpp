#include <iostream>
#include <vector>
#include <algorithm>
#include <queue> 

using namespace std;

template <typename T>
class BTreeNode {
public: 
    vector<T> dataset;
    vector<BTreeNode<T>*> children;

    BTreeNode(vector<T> init_dataset, vector<BTreeNode<T>*> init_children) {
        dataset = init_dataset;
        children = init_children;
    }

    void insert(T data) {
        dataset.push_back(data);
        sort(dataset.begin(), dataset.end());
    }

    bool is_leaf() {
        return (children.size() == 0);
    }


    void split_child(int index) {
        int mid = children[index]->dataset.size() / 2;
        insert(children[index]->dataset[mid]);

        vector<T> left_dataset;
        vector<T> right_dataset;
        vector<BTreeNode<T>*> left_children;
        vector<BTreeNode<T>*> right_children;

        for (int i = 0; i < children[index]->dataset.size(); i++) {
            if (i < mid) {
                left_dataset.push_back(children[index]->dataset[i]);
            }
            else if (i > mid) {
                right_dataset.push_back(children[index]->dataset[i]);
            }
        }

        if (!children[index]->is_leaf()) {
            for (int i = 0; i < children[index]->children.size(); i++) {
                if (i <= mid) {
                    left_children.push_back(children[index]->children[i]);
                }
                else if (i > mid) {
                    right_children.push_back(children[index]->children[i]);
                }
            }
        }

        BTreeNode<T>* left_child = new BTreeNode(left_dataset, left_children);
        BTreeNode<T>* right_child = new BTreeNode(right_dataset, right_children);

        children[index] = right_child;
        children.insert(children.begin() + index, left_child);
    }

    void print_data() {
        cout << "[ ";
        for (int i = 0; i < dataset.size(); i++) {
            cout << dataset[i] << " ";
        }
        cout << "]";
    }
};

template <typename T>
class BTree {
private:
    int M;
    BTreeNode<T>* root_ptr;

    BTreeNode<T>* search_recursion(BTreeNode<T>* node, T data) {
        if (node->is_leaf()) {
            for (int i = 0; i < node->dataset.size(); i++) {
                if (data == node->dataset[i])
                    return node;
            }
            return nullptr;
        }

        if (data < node->dataset[0])
            return search_recursion(node->children[0], data);
        else if (data == node->dataset[0])
            return node;
        for (int i = 1; i < node->dataset.size(); i++) {
            if (data > node->dataset[i - 1] && data < node->dataset[i])
                return search_recursion(node->children[i], data);
            else if (data == node->dataset[i])
                return node;
        }
        if (data > node->dataset.back())
            return search_recursion(node->children[node->dataset.size()], data);

        return nullptr;
    }

    BTreeNode<T>* find_parent(BTreeNode<T>* node, BTreeNode<T>* target) {
        for (int i = 0; i < node->children.size(); i++) {
            if (target == node->children[i])
                return node;
        }

        T data = target->dataset[0];
        if (data <= node->dataset[0])
            return find_parent(node->children[0], target);
        for (int i = 1; i < node->dataset.size(); i++) {
            if (data > node->dataset[i - 1] && data <= node->dataset[i])
                return find_parent(node->children[i], target);
        }
        if (data > node->dataset.back())
            return find_parent(node->children[node->dataset.size()], target);

        return nullptr;
    }

    BTreeNode<T>* find_suitable(BTreeNode<T>* node, T data) {
        if (node->is_leaf())
            return node;

        if (data <= node->dataset[0])
            return find_suitable(node->children[0], data);
        for (int i = 1; i < node->dataset.size(); i++) {
            if (data > node->dataset[i - 1] && data <= node->dataset[i])
                return find_suitable(node->children[i], data);
        }
        if (data > node->dataset.back())
            return find_suitable(node->children[node->dataset.size()], data);

        return nullptr;
    }

    void fix_excess(BTreeNode<T>* node) {
        if (node->dataset.size() < M)
            return;

        if (node == root_ptr) { 
            BTreeNode<T>* new_root = new BTreeNode<T>(vector<T>(), vector<BTreeNode<T>*>(1, root_ptr));
            new_root->split_child(0);
            root_ptr = new_root;
        }
        else {
            BTreeNode<T>* parent = find_parent(root_ptr, node);

            int split_index = 0;
            for (int i = 0; i < parent->children.size(); i++) {
                if (node == parent->children[i]) {
                    split_index = i;
                    break;
                }
            }

            parent->split_child(split_index);
            fix_excess(parent);
        }
    }


public:
    BTree(int M = 3, BTreeNode<T>* init_root = nullptr) {
        this->M = M;
        root_ptr = init_root;
    }

    // 데이터 탐색
    bool search(T data) {
        BTreeNode<T>* result = search_recursion(root_ptr, data);
        if (result == nullptr)
            return false;
        else
            return true;
    }

    // 데이터 삽입
    void insert(T data) {
        if (root_ptr == nullptr) {
            BTreeNode<T>* new_root = new BTreeNode<T>(vector<T>(1, data), vector<BTreeNode<T>*>());
            root_ptr = new_root;
        }
        else {
            BTreeNode<T>* suitable_node = find_suitable(root_ptr, data);
            suitable_node->insert(data);
            fix_excess(suitable_node);
        }
    }

    void print_tree() {
        queue<BTreeNode<T>*>* node_queue = new queue<BTreeNode<T>*>();
        int current_level = 0;
        int next_level = 0;
        int count = 0;

        node_queue->push(root_ptr);
        root_ptr->print_data();
        cout << endl;

        while (!node_queue->empty()) {
            BTreeNode<T>* node = node_queue->front();
            node_queue->pop();

            if (!node->is_leaf()) {
                cout << "[";
                for (int i = 0; i < node->children.size(); i++) {
                    node_queue->push(node->children[i]);
                    node->children[i]->print_data();
                    next_level++;
                }
                cout << "] ";
            }

            count++;
            if (count >= current_level) {
                cout << endl;
                current_level = next_level;
                next_level = 0;
                count = 0;
            }
        }
    }
};