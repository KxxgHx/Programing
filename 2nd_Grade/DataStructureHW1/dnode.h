#ifndef DNODE_H
#define DNODE_H

#include <cstdlib>
#include <cassert>

template <class Item>
class dnode {
public:
    typedef Item value_type;
    
    // constructor
    dnode(
        const Item& init_data = Item(),
        dnode* init_prev = NULL,
        dnode* init_next = NULL
    ) {
        data_field = init_data;
        prev_field = init_prev;
        next_field = init_next;
    }
    
    // member function
    void set_data(const Item& new_data) { data_field = new_data; }
    void set_prev(dnode* new_prev) { prev_field = new_prev; }
    void set_next(dnode* new_next) { next_field = new_next; }
    
    // const member function
    Item data() const { return data_field; }
    Item& data() { return data_field; }
    const dnode* prev() const { return prev_field; }
    dnode* prev() { return prev_field; }
    const dnode* next() const { return next_field; }
    dnode* next() { return next_field; }
    
private:
    Item data_field;
    dnode* prev_field;
    dnode* next_field;
};

template <class Item>
size_t list_length(const dnode<Item>* head_ptr);

template <class Item>
dnode<Item>* list_search(dnode<Item>* head_ptr, const Item& target);

template <class Item>
const dnode<Item>* list_search(const dnode<Item>* head_ptr, const Item& target);

template <class Item>
dnode<Item>* list_locate(dnode<Item>* head_ptr, size_t position);

template <class Item>
const dnode<Item>* list_locate(const dnode<Item>* head_ptr, size_t position);

template <class Item>
void list_copy(const dnode<Item>* source_ptr, dnode<Item>*& head_ptr, dnode<Item>*& tail_ptr);

template <class Item>
bool list_head_insert(dnode<Item>*& head_ptr, dnode<Item>*& tail_ptr, const Item& entry);

template <class Item>
bool list_tail_insert(dnode<Item>*& head_ptr, dnode<Item>*& tail_ptr, const Item& entry);

template <class Item>
bool list_insert(dnode<Item>* previous_ptr, const Item& entry);

template <class Item>
void list_head_remove(dnode<Item>*& head_ptr, dnode<Item>*& tail_ptr);

template <class Item>
void list_tail_remove(dnode<Item>*& head_ptr, dnode<Item>*& tail_ptr);

template <class Item>
void list_remove(dnode<Item>*& head_ptr, dnode<Item>*& tail_ptr, dnode<Item>* remove_ptr);

template <class Item>
void list_clear(dnode<Item>*& head_ptr, dnode<Item>*& tail_ptr);

template <class Item>
size_t list_length(const dnode<Item>* head_ptr) {
    size_t answer = 0;
    for (const dnode<Item>* cursor = head_ptr; cursor != NULL; cursor = cursor->next())
        ++answer;
    return answer;
}

template <class Item>
dnode<Item>* list_search(dnode<Item>* head_ptr, const Item& target) {
    for (dnode<Item>* cursor = head_ptr; cursor != NULL; cursor = cursor->next())
        if (target == cursor->data())
            return cursor;
    return NULL;
}

template <class Item>
const dnode<Item>* list_search(const dnode<Item>* head_ptr, const Item& target) {
    for (const dnode<Item>* cursor = head_ptr; cursor != NULL; cursor = cursor->next())
        if (target == cursor->data())
            return cursor;
    return NULL;
}

template <class Item>
dnode<Item>* list_locate(dnode<Item>* head_ptr, size_t position) {
    assert(0 < position);
    dnode<Item>* cursor = head_ptr;
    for (size_t i = 1; (i < position) && (cursor != NULL); ++i)
        cursor = cursor->next();
    return cursor;
}

template <class Item>
const dnode<Item>* list_locate(const dnode<Item>* head_ptr, size_t position) {
    assert(0 < position);
    const dnode<Item>* cursor = head_ptr;
    for (size_t i = 1; (i < position) && (cursor != NULL); ++i)
        cursor = cursor->next();
    return cursor;
}

template <class Item>
void list_copy(const dnode<Item>* source_ptr, dnode<Item>*& head_ptr, dnode<Item>*& tail_ptr) {
    head_ptr = NULL;
    tail_ptr = NULL;
    
    if (source_ptr == NULL)
        return;
    
    head_ptr = new dnode<Item>(source_ptr->data());
    tail_ptr = head_ptr;
    
    for (source_ptr = source_ptr->next(); source_ptr != NULL; source_ptr = source_ptr->next()) {
        dnode<Item>* new_node = new dnode<Item>(source_ptr->data(), tail_ptr);
        tail_ptr->set_next(new_node);
        tail_ptr = new_node;
    }
}

template <class Item>
bool list_head_insert(dnode<Item>*& head_ptr, dnode<Item>*& tail_ptr, const Item& entry) {
    if (list_search(head_ptr, entry) != NULL)
        return false;
    
    dnode<Item>* new_node = new dnode<Item>(entry, NULL, head_ptr);
    
    if (head_ptr != NULL)
        head_ptr->set_prev(new_node);
    else
        tail_ptr = new_node;
    
    head_ptr = new_node;
    return true;
}

template <class Item>
bool list_tail_insert(dnode<Item>*& head_ptr, dnode<Item>*& tail_ptr, const Item& entry) {
    if (list_search(head_ptr, entry) != NULL)
        return false;
    
    dnode<Item>* new_node = new dnode<Item>(entry, tail_ptr, NULL);
    
    if (tail_ptr != NULL)
        tail_ptr->set_next(new_node);
    else
        head_ptr = new_node;
    
    tail_ptr = new_node;
    return true;
}

template <class Item>
bool list_insert(dnode<Item>* previous_ptr, const Item& entry) {
    if (previous_ptr == NULL)
        return false;
    
    dnode<Item>* head_ptr = previous_ptr;
    while (head_ptr->prev() != NULL)
        head_ptr = head_ptr->prev();
    
    if (list_search(head_ptr, entry) != NULL)
        return false;
    
    dnode<Item>* new_node = new dnode<Item>(entry, previous_ptr, previous_ptr->next());
    
    if (previous_ptr->next() != NULL)
        previous_ptr->next()->set_prev(new_node);
    
    previous_ptr->set_next(new_node);
    return true;
}

template <class Item>
void list_head_remove(dnode<Item>*& head_ptr, dnode<Item>*& tail_ptr) {
    if (head_ptr == NULL)
        return;
    
    dnode<Item>* remove_ptr = head_ptr;
    head_ptr = head_ptr->next();
    
    if (head_ptr != NULL)
        head_ptr->set_prev(NULL);
    else
        tail_ptr = NULL;
    
    delete remove_ptr;
}

template <class Item>
void list_tail_remove(dnode<Item>*& head_ptr, dnode<Item>*& tail_ptr) {
    if (tail_ptr == NULL)
        return;
    
    dnode<Item>* remove_ptr = tail_ptr;
    tail_ptr = tail_ptr->prev();
    
    if (tail_ptr != NULL)
        tail_ptr->set_next(NULL);
    else
        head_ptr = NULL;
    
    delete remove_ptr;
}

template <class Item>
void list_remove(dnode<Item>*& head_ptr, dnode<Item>*& tail_ptr, dnode<Item>* remove_ptr) {
    if (remove_ptr == NULL)
        return;
    
    if (remove_ptr->prev() != NULL)
        remove_ptr->prev()->set_next(remove_ptr->next());
    else
        head_ptr = remove_ptr->next();
    
    if (remove_ptr->next() != NULL)
        remove_ptr->next()->set_prev(remove_ptr->prev());
    else
        tail_ptr = remove_ptr->prev();
    
    delete remove_ptr;
}

template <class Item>
void list_clear(dnode<Item>*& head_ptr, dnode<Item>*& tail_ptr) {
    while (head_ptr != NULL)
        list_head_remove(head_ptr, tail_ptr);
}

#endif