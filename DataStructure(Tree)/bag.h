#ifndef BAG_H
#define BAG_H

#include "binary_tree_node.h"
#include <iostream>
#include <cstddef> 

namespace BST
{
    template <class Item>
    class bag
    {
    public:
        typedef std::size_t size_type;

        bag() : root_ptr(NULL) {}
        bag(const bag &source) : root_ptr(BST::tree_copy(source.root_ptr)) {}
        ~bag() { BST::tree_clear(root_ptr); }

        void insert(const Item &entry) { BST::bst_insert(root_ptr, entry); }
        bool erase_one(const Item &target) { return BST::bst_remove(root_ptr, target); }
        void operator+=(const bag &addend);
        void operator=(const bag &source);

        size_type size() const { return BST::tree_size(root_ptr); }

        const binary_tree_node<Item>* get_root() const 
        { 
            return root_ptr;
        }
    private:
        binary_tree_node<Item> *root_ptr;
        void insert_all(const binary_tree_node<Item> *tree_ptr);
    };

    // --- bag 멤버 함수 정의 ---

    template <class Item>
    void bag<Item>::insert_all(const binary_tree_node<Item> *tree_ptr)
    {
        if(tree_ptr != NULL)
        {
            insert(tree_ptr->data());
            insert_all(tree_ptr->left());
            insert_all(tree_ptr->right());
        }
    }

    template <class Item>
    void bag<Item>::operator=(const bag &source)
    {
        if(this == &source)
            return;

        BST::tree_clear(root_ptr);
        root_ptr = BST::tree_copy(source.root_ptr);
    }

    template <class Item>
    void bag<Item>::operator+=(const bag &addend)
    {
        if(this == &addend)
        {
            binary_tree_node<Item> *addroot_ptr = BST::tree_copy(root_ptr);
            insert_all(addroot_ptr);
            BST::tree_clear(addroot_ptr);
        }
        else
        {
            insert_all(addend.root_ptr);
        }
    }
}

#endif