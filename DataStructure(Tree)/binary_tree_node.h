#ifndef BINARY_TREE_NODE_H
#define BINARY_TREE_NODE_H

#include <iostream>
#include <cstddef>

namespace BST
{
    template <class Item> class bag; 

    template<class Item> class binary_tree_node{
    public:
        // Constructor
        binary_tree_node(const Item &init_data = Item(), binary_tree_node *init_left = NULL, binary_tree_node *init_right = NULL) 
        {
            data_field = init_data;
            left_field = init_left;
            right_field = init_right;
        }

        void set_data(const Item &new_data) { data_field = new_data; }
        void set_left(binary_tree_node *new_left) { left_field = new_left; }
        void set_right(binary_tree_node *new_right) { right_field = new_right; }

        Item &data() { return data_field; }
        binary_tree_node *&left() { return left_field; }
        binary_tree_node *&right() { return right_field; }

        const Item &data() const { return data_field; }
        const binary_tree_node *left() const { return left_field; }
        const binary_tree_node *right() const { return right_field; }
        bool is_leaf() const 
        {
            return (left_field == NULL && right_field == NULL);
        }

    private:
        Item data_field;
        binary_tree_node *left_field;
        binary_tree_node *right_field;

        template <class ItemT>
        friend class bag;
    };


    template <class Item>
    void bst_remove_max(binary_tree_node<Item> *&root_ptr, Item &removed){
        if (root_ptr->right() == NULL){
            removed = root_ptr->data();
            binary_tree_node<Item> *oldroot_ptr = root_ptr;
            root_ptr = root_ptr->left();
            delete oldroot_ptr;
            return;
        }
        bst_remove_max(root_ptr->right(), removed);
    }

    template <class Item>
    void tree_clear(binary_tree_node<Item> *&root_ptr)
    {
        if (root_ptr != NULL){
            tree_clear(root_ptr->left());
            tree_clear(root_ptr->right());
            delete root_ptr;
            root_ptr = NULL;
        }
    }

    template <class Item>
    binary_tree_node<Item> *tree_copy(const binary_tree_node<Item> *root_ptr){
        binary_tree_node<Item> *l_ptr;
        binary_tree_node<Item> *r_ptr;

        if(root_ptr == NULL)
            return NULL;

        l_ptr = tree_copy(root_ptr->left());
        r_ptr = tree_copy(root_ptr->right());

        return new binary_tree_node<Item>(root_ptr->data(), l_ptr, r_ptr);
    }

    template <class Item>
    size_t tree_size(const binary_tree_node<Item>* root_ptr){
        if(root_ptr == NULL)
            return 0;

        return 1 + tree_size(root_ptr->left()) + tree_size(root_ptr->right());
    }

    template <class Item>
    void bst_insert(binary_tree_node<Item> *&root_ptr, const Item &entry){
        if(root_ptr == NULL){
            root_ptr = new binary_tree_node<Item>(entry);
            return;
        }

        binary_tree_node<Item> *cursor = root_ptr;
        bool done = false;

        while(!done){
            if (entry <= cursor->data()){
                if (cursor->left() == NULL){
                    cursor->set_left(new binary_tree_node<Item>(entry));
                    done = true;
                }
                else
                {
                    cursor = cursor->left();
                }
            }
            else
            {
                if (cursor->right() == NULL){
                    cursor->set_right(new binary_tree_node<Item>(entry));
                    done = true;
                }
                else
                {
                    cursor = cursor->right();
                }
            }
        }
    }

    template <class Item>
    bool bst_remove(binary_tree_node<Item> *&root_ptr, const Item &target){
        if(root_ptr == NULL)
            return false;

        if (target < root_ptr->data())
        {
            return bst_remove(root_ptr->left(), target);
        }
        else if (target > root_ptr->data())
        {
            return bst_remove(root_ptr->right(), target);
        }
        else // target == root_ptr->data()
        {
            if (root_ptr->left() == NULL)
            {
                binary_tree_node<Item> *oldroot_ptr = root_ptr;
                root_ptr = root_ptr->right();
                delete oldroot_ptr;
                return true;
            } else {
                Item removed_item;
                bst_remove_max(root_ptr->left(), removed_item);
                root_ptr->set_data(removed_item);
                return true;
            }
        }
    }

}

#endif