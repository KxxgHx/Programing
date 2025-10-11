#ifndef OURSET_H
#define OURSET_H

#include <cstdlib>
#include <iostream>
#include <cassert>
#include "dnode.h"


template <class Item>
class OurSet {
public:
    typedef Item value_type;
    typedef size_t size_type;
    
    OurSet();
    OurSet(const OurSet& source);
    ~OurSet();
    
    bool insert(const Item& entry);
    bool erase(const Item& target);
    void operator +=(const OurSet& addend);
    void operator =(const OurSet& source);
    void sort();
    void sort_with_iterator();
    
    size_type size() const { return many_nodes; }
    size_type count(const Item& target) const;
    void show_contents() const;
    
    // itrerator을 활용한 sort
    class iterator {
    public:
        iterator(dnode<Item>* init = NULL) : current(init) { }
        
        Item& operator *();
        iterator& operator ++();      // Prefix ++
        iterator operator ++(int);    // Postfix ++
        bool operator ==(const iterator& other) const;
        bool operator !=(const iterator& other) const;
        
        friend class OurSet<Item>;
    private:
        dnode<Item>* current;
    };
    
    iterator begin();
    iterator end();
    
private:
    dnode<Item>* head_ptr;
    dnode<Item>* tail_ptr;
    size_type many_nodes;
};

template <class Item>
OurSet<Item> operator +(const OurSet<Item>& s1, const OurSet<Item>& s2);

template <class Item>
bool operator ==(const OurSet<Item>& s1, const OurSet<Item>& s2);

template <class Item>
bool operator !=(const OurSet<Item>& s1, const OurSet<Item>& s2);

template <class Item>
OurSet<Item>::OurSet()
{
    head_ptr = NULL;
    tail_ptr = NULL;
    many_nodes = 0;
}

template <class Item>
OurSet<Item>::OurSet(const OurSet& source)
{
    dnode<Item>* tail;
    list_copy(source.head_ptr, head_ptr, tail);
    tail_ptr = tail;
    many_nodes = source.many_nodes;
}

template <class Item>
OurSet<Item>::~OurSet()
{
    list_clear(head_ptr, tail_ptr);
    many_nodes = 0;
}

template <class Item>
bool OurSet<Item>::insert(const Item& entry)
{
    if (list_tail_insert(head_ptr, tail_ptr, entry)) {
        ++many_nodes;
        return true;
    }
    return false;
}

template <class Item>
bool OurSet<Item>::erase(const Item& target)
{
    dnode<Item>* target_ptr = list_search(head_ptr, target);
    
    if (target_ptr == NULL)
        return false;
    
    list_remove(head_ptr, tail_ptr, target_ptr);
    --many_nodes;
    return true;
}

template <class Item>
typename OurSet<Item>::size_type OurSet<Item>::count(const Item& target) const
{
    return (list_search(head_ptr, target) != NULL) ? 1 : 0;
}

template <class Item>
void OurSet<Item>::show_contents() const
{
    std::cout << "{ ";
    
    for (const dnode<Item>* cursor = head_ptr; cursor != NULL; cursor = cursor->next()) {
        std::cout << cursor->data();
        if (cursor->next() != NULL)
            std::cout << ", ";
    }
    
    std::cout << " }";
}

template <class Item>
void OurSet<Item>::operator +=(const OurSet& addend)
{
    for (const dnode<Item>* cursor = addend.head_ptr; cursor != NULL; cursor = cursor->next())
        insert(cursor->data());
}

template <class Item>
void OurSet<Item>::operator =(const OurSet& source)
{
    if (this == &source)
        return;
    
    list_clear(head_ptr, tail_ptr);
    
    dnode<Item>* tail;
    list_copy(source.head_ptr, head_ptr, tail);
    tail_ptr = tail;
    many_nodes = source.many_nodes;
}

template <class Item>
void OurSet<Item>::sort()
{
    if (head_ptr == NULL || head_ptr->next() == NULL)
        return;
    
    bool swapped;
    do {
        swapped = false;
        dnode<Item>* current = head_ptr;
        
        while (current->next() != NULL) {
            if (current->data() > current->next()->data()) {
                Item temp = current->data();
                current->set_data(current->next()->data());
                current->next()->set_data(temp);
                swapped = true;
            }
            current = current->next();
        }
    } while (swapped);
}

template <class Item>
void OurSet<Item>::sort_with_iterator()
{
    if (head_ptr == NULL || head_ptr->next() == NULL)
        return;
    
    bool swapped;
    do {
        swapped = false;
        iterator it1 = begin();
        iterator it2 = begin();
        ++it2;
        
        while (it2 != end()) {
            if (*it1 > *it2) {
                Item temp = *it1;
                *it1 = *it2;
                *it2 = temp;
                swapped = true;
            }
            ++it1;
            ++it2;
        }
    } while (swapped);
}

template <class Item>
Item& OurSet<Item>::iterator::operator *()
{
    assert(current != NULL);
    return current->data();
}

template <class Item>
typename OurSet<Item>::iterator& OurSet<Item>::iterator::operator ++()
{
    if (current != NULL)
        current = current->next();
    return *this;
}

template <class Item>
typename OurSet<Item>::iterator OurSet<Item>::iterator::operator ++(int)
{
    iterator temp = *this;
    ++(*this);
    return temp;
}

template <class Item>
bool OurSet<Item>::iterator::operator ==(const iterator& other) const
{
    return current == other.current;
}

template <class Item>
bool OurSet<Item>::iterator::operator !=(const iterator& other) const
{
    return current != other.current;
}

template <class Item>
typename OurSet<Item>::iterator OurSet<Item>::begin()
{
    return iterator(head_ptr);
}

template <class Item>
typename OurSet<Item>::iterator OurSet<Item>::end()
{
    return iterator(NULL);
}


template <class Item>
OurSet<Item> operator +(const OurSet<Item>& s1, const OurSet<Item>& s2)
{
    OurSet<Item> result(s1);
    result += s2;
    return result;
}

template <class Item>
bool operator ==(const OurSet<Item>& s1, const OurSet<Item>& s2)
{
    if (s1.size() != s2.size())
        return false;
    

    typename OurSet<Item>::iterator it;
    OurSet<Item>& non_const_s1 = const_cast<OurSet<Item>&>(s1);
    
    for (it = non_const_s1.begin(); it != non_const_s1.end(); ++it) {
        if (s2.count(*it) == 0)
            return false;
    }
    
    return true;
}

template <class Item>
bool operator !=(const OurSet<Item>& s1, const OurSet<Item>& s2)
{
    return !(s1 == s2);
}

#endif