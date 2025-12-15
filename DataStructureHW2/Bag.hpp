#ifndef BAG_H
#define BAG_H

#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

template <class Item, std::size_t SomePosNumber = 1>
class bag
{
public:
    // TYPEDEFS
    typedef Item value_type;
    // CONSTRUCTORS and DESTRUCTOR
    bag();
    bag(const bag& source);
    ~bag() { clear(); }
    // MODIFICATION MEMBER FUNCTIONS
    void operator =(const bag& source);
    void clear();
    bool insert(const Item& entry);
    bool erase_one(const Item& target);
    bool erase_all(const Item& target);
    // CONSTANT MEMBER FUNCTIONS
    std::size_t count(const Item& target) const;
    bool empty() const { return (data_count == 0); }
    // SUGGESTED FUNCTION FOR DEBUGGING
    void show_contents (int indent) const;
private:
    // MEMBER CONSTANTS
    static const std::size_t MINIMUM = SomePosNumber;
    static const std::size_t MAXIMUM = 2 * MINIMUM;
    // MEMBER VARIABLES
    std::size_t data_count;
    Item data[MAXIMUM+1];
    std::size_t child_count;
    bag *subbag[MAXIMUM+2];
    // HELPER MEMBER FUNCTIONS
    bool is_leaf() const { return (child_count == 0); }
    bool loose_insert(const Item& entry);
    bool loose_erase(const Item& target);
    void remove_biggest(Item& removed_entry);
    void fix_excess(std::size_t i);
    void fix_shortage(std::size_t i);
};

// -------------------------------------------------------------------------
// IMPLEMENTATION
// -------------------------------------------------------------------------

template <class Item, std::size_t SomePosNumber>
bag<Item, SomePosNumber>::bag()
{
    data_count = 0;
    child_count = 0;
    for (size_t i = 0; i < MAXIMUM + 2; i++)
    {
        subbag[i] = nullptr;
    }
}

template <class Item, std::size_t SomePosNumber>
bag<Item, SomePosNumber>::bag(const bag<Item, SomePosNumber>& source)
{
    data_count = source.data_count;
    child_count = source.child_count;

    // 먼저 모든 포인터 초기화
    for (size_t i = 0; i < MAXIMUM + 2; ++i) {
        subbag[i] = nullptr;
    }

    // 데이터 복사
    for (size_t i = 0; i < data_count; ++i) {
        data[i] = source.data[i];
    }

    // 자식 노드 깊은 복사
    for (size_t i = 0; i < child_count; ++i) {
        if (source.subbag[i] != nullptr) {
            subbag[i] = new bag<Item, SomePosNumber>(*source.subbag[i]);
        }
    }
}

template <class Item, std::size_t SomePosNumber>
void bag<Item, SomePosNumber>::operator=(const bag<Item, SomePosNumber>& source)
{
    if (this == &source)
        return;

    clear();

    data_count = source.data_count;
    child_count = source.child_count;

    for (size_t i = 0; i < data_count; ++i) {
        data[i] = source.data[i];
    }

    for (size_t i = 0; i < child_count; ++i) {
        if (source.subbag[i] != nullptr) {
            subbag[i] = new bag<Item, SomePosNumber>(*source.subbag[i]);
        }
    }
    
    for (size_t i = child_count; i < MAXIMUM + 2; ++i) {
        subbag[i] = nullptr;
    }
}

template <class Item, std::size_t SomePosNumber>
void bag<Item, SomePosNumber>::clear()
{
    for (size_t i = 0; i < child_count; ++i) {
        if (subbag[i] != nullptr) {
            subbag[i]->clear();
            delete subbag[i];
            subbag[i] = nullptr;
        }
    }
    data_count = 0;
    child_count = 0;
}

template <class Item, std::size_t SomePosNumber>
bool bag<Item, SomePosNumber>::insert(const Item& entry)
{
    if (!loose_insert(entry)) return false;

    if (data_count > MAXIMUM)
    {
        bag<Item, SomePosNumber> *new_root_child = new bag<Item, SomePosNumber>();
        
        new_root_child->data_count = data_count;
        new_root_child->child_count = child_count;
        
        for (size_t i = 0; i < data_count; i++)
            new_root_child->data[i] = data[i];
        
        for (size_t i = 0; i < child_count; i++)
            new_root_child->subbag[i] = subbag[i];

        // 나머지 포인터 nullptr로 초기화
        for (size_t i = child_count; i < MAXIMUM + 2; i++)
            new_root_child->subbag[i] = nullptr;

        data_count = 0;
        child_count = 1; 
        subbag[0] = new_root_child;

        for (size_t i = 1; i < MAXIMUM + 2; i++)
             subbag[i] = nullptr;

        fix_excess(0);
    }
    return true;
}

template <class Item, std::size_t SomePosNumber>
bool bag<Item, SomePosNumber>::loose_insert(const Item& entry)
{
    size_t i = 0;
    while (i < data_count && data[i] < entry) i++;
    
    if (i < data_count && data[i] == entry) i++;

    if(is_leaf())
    {
        for (size_t j = data_count; j > i; j--)
        {
            data[j] = data[j - 1];
        }
        data[i] = entry;
        data_count++;
        return true;
    }
    else
    {
        bool b = subbag[i]->loose_insert(entry);
        
        if(subbag[i]->data_count > MAXIMUM)
            fix_excess(i);

        return b;
    }             
}

template <class Item, std::size_t SomePosNumber>
void bag<Item, SomePosNumber>::fix_excess(std::size_t i)
{
    bag* child = subbag[i];
    bag* right_node = new bag<Item, SomePosNumber>();
    
    size_t split_point = MINIMUM; 
    
    // 오른쪽 노드로 데이터 이동
    size_t right_items = child->data_count - (split_point + 1);
    for (size_t j = 0; j < right_items; j++)
        right_node->data[j] = child->data[split_point + 1 + j];
    right_node->data_count = right_items;

    // 오른쪽 노드로 자식 이동
    if (!child->is_leaf()) {
        size_t right_children = child->child_count - (split_point + 1);
        for (size_t j = 0; j < right_children; ++j)
            right_node->subbag[j] = child->subbag[split_point + 1 + j];
        right_node->child_count = right_children;
        
        // 나머지 포인터 nullptr로 설정
        for (size_t j = right_children; j < MAXIMUM + 2; ++j)
            right_node->subbag[j] = nullptr;
    }

    // 부모 노드에 중간값 삽입
    for (size_t j = data_count; j > i; --j) data[j] = data[j-1];
    data[i] = child->data[split_point];
    data_count++;

    // 부모 노드에 오른쪽 자식 추가
    for (size_t j = child_count; j > i + 1; --j) subbag[j] = subbag[j-1];
    subbag[i+1] = right_node;
    child_count++;

    // 왼쪽 자식 크기 조정
    child->data_count = split_point;
    if (!child->is_leaf()) {
        child->child_count = split_point + 1;
        // 사용하지 않는 포인터 nullptr로 설정
        for (size_t j = child->child_count; j < MAXIMUM + 2; ++j)
            child->subbag[j] = nullptr;
    }
}

template <class Item, std::size_t SomePosNumber>
bool bag<Item, SomePosNumber>::erase_one(const Item& target)
{
    if(!loose_erase(target))
        return false;

    if (data_count == 0 && child_count == 1)
    {
        bag *old_child = subbag[0];

        data_count = old_child->data_count;
        child_count = old_child->child_count;

        for (size_t i = 0; i < data_count; i++)
            data[i] = old_child->data[i];
        for (size_t i = 0; i < child_count; i++)
            subbag[i] = old_child->subbag[i];

        // 나머지 포인터 nullptr로
        for (size_t i = child_count; i < MAXIMUM + 2; i++)
            subbag[i] = nullptr;

        old_child->child_count = 0;
        delete old_child;
    }
    return true;
}

template <class Item, std::size_t SomePosNumber>
bool bag<Item, SomePosNumber>::erase_all(const Item& target)
{
    bool removed = false;
    while(erase_one(target)) {
        removed = true;
    }
    return removed;
}

template <class Item, std::size_t SomePosNumber>
bool bag<Item, SomePosNumber>::loose_erase(const Item& target)
{
    size_t i = 0;
    while (i < data_count && data[i] < target) i++;

    if (i < data_count && data[i] == target)
    {
        if(is_leaf())
        {
            for (size_t j = i; j < data_count - 1; j++)
                data[j] = data[j + 1];
            data_count--;
            return true;
        }
        else
        {
            subbag[i]->remove_biggest(data[i]);
            if (subbag[i]->data_count < MINIMUM)
                fix_shortage(i);
            return true;
        }
    }
    else
    {
        if(is_leaf()) return false;

        bool b = subbag[i]->loose_erase(target);
        if (subbag[i]->data_count < MINIMUM)
            fix_shortage(i);
        return b;
    }
}

template <class Item, std::size_t SomePosNumber>
void bag<Item, SomePosNumber>::remove_biggest(Item& removed_entry)
{
    if(is_leaf())
    {
        removed_entry = data[data_count - 1];
        data_count--;
    }
    else
    {
        subbag[child_count - 1]->remove_biggest(removed_entry);
        if (subbag[child_count - 1]->data_count < MINIMUM)
            fix_shortage(child_count - 1);
    }
}

template <class Item, std::size_t SomePosNumber>
void bag<Item, SomePosNumber>::fix_shortage(std::size_t i)
{
    // 왼쪽 형제에서 빌려오기
    if (i > 0 && subbag[i - 1]->data_count > MINIMUM)
    {
        for (size_t j = subbag[i]->data_count; j > 0; j--)
            subbag[i]->data[j] = subbag[i]->data[j - 1];
        
        subbag[i]->data[0] = data[i - 1];
        subbag[i]->data_count++;
        data[i - 1] = subbag[i - 1]->data[subbag[i - 1]->data_count - 1];

        if(!subbag[i]->is_leaf())
        {
            for (size_t j = subbag[i]->child_count; j > 0; j--)
                subbag[i]->subbag[j] = subbag[i]->subbag[j - 1];

            subbag[i]->subbag[0] = subbag[i - 1]->subbag[subbag[i - 1]->child_count - 1];
            subbag[i]->child_count++;
            subbag[i - 1]->subbag[subbag[i - 1]->child_count - 1] = nullptr;
            subbag[i - 1]->child_count--;
        }
        subbag[i - 1]->data_count--;
    }
    // 오른쪽 형제에서 빌려오기
    else if (i < child_count - 1 && subbag[i + 1]->data_count > MINIMUM)
    {
        subbag[i]->data[subbag[i]->data_count] = data[i];
        subbag[i]->data_count++;
        data[i] = subbag[i+1]->data[0];
        
        if (!subbag[i]->is_leaf()) {
            subbag[i]->subbag[subbag[i]->child_count] = subbag[i+1]->subbag[0];
            subbag[i]->child_count++;
            
            for (size_t j = 0; j < subbag[i+1]->child_count - 1; ++j)
                subbag[i+1]->subbag[j] = subbag[i+1]->subbag[j+1];
            subbag[i+1]->subbag[subbag[i+1]->child_count - 1] = nullptr;
            subbag[i+1]->child_count--;
        }
        
        for (size_t j = 0; j < subbag[i+1]->data_count - 1; ++j)
            subbag[i+1]->data[j] = subbag[i+1]->data[j+1];
        subbag[i+1]->data_count--;
    }
    // 왼쪽 형제와 병합
    else if (i > 0) {
        subbag[i-1]->data[subbag[i-1]->data_count] = data[i-1];
        subbag[i-1]->data_count++;
        
        for (size_t j = 0; j < subbag[i]->data_count; ++j)
            subbag[i-1]->data[subbag[i-1]->data_count++] = subbag[i]->data[j];
        
        if (!subbag[i]->is_leaf()) {
            for (size_t j = 0; j < subbag[i]->child_count; ++j)
                subbag[i-1]->subbag[subbag[i-1]->child_count++] = subbag[i]->subbag[j];
        }
        
        subbag[i]->child_count = 0; // 자식 포인터 소유권 이전
        delete subbag[i];
        
        for (size_t j = i-1; j < data_count - 1; ++j) 
            data[j] = data[j+1];
        for (size_t j = i; j < child_count - 1; ++j) 
            subbag[j] = subbag[j+1];
        
        subbag[child_count - 1] = nullptr;
        data_count--;
        child_count--;
    }
    // 오른쪽 형제와 병합
    else {
        subbag[i]->data[subbag[i]->data_count] = data[i];
        subbag[i]->data_count++;
        
        for (size_t j = 0; j < subbag[i+1]->data_count; ++j)
            subbag[i]->data[subbag[i]->data_count++] = subbag[i+1]->data[j];
        
        if (!subbag[i]->is_leaf()) {
            for (size_t j = 0; j < subbag[i+1]->child_count; ++j)
                subbag[i]->subbag[subbag[i]->child_count++] = subbag[i+1]->subbag[j];
        }
        
        subbag[i+1]->child_count = 0; // 자식 포인터 소유권 이전
        delete subbag[i+1];
        
        for (size_t j = i; j < data_count - 1; ++j) 
            data[j] = data[j+1];
        for (size_t j = i + 1; j < child_count - 1; ++j) 
            subbag[j] = subbag[j+1];
        
        subbag[child_count - 1] = nullptr;
        data_count--;
        child_count--;
    }
}

template <class Item, std::size_t SomePosNumber>
std::size_t bag<Item, SomePosNumber>::count(const Item& target) const
{
    size_t answer = 0;
    size_t i = 0;

    // 현재 노드에서 target 개수 세기
    while (i < data_count && data[i] < target) i++;
    
    while (i < data_count && data[i] == target) {
        answer++;
        i++;
    }

    // 자식 노드에서 재귀적으로 개수 세기
    if (!is_leaf()) {
        i = 0;
        while (i < data_count && data[i] < target) i++;
        
        if (i < child_count && subbag[i] != nullptr)
            answer += subbag[i]->count(target);
        
        // target과 같은 값들 뒤의 자식도 확인
        while (i < data_count && data[i] == target) {
            i++;
            if (i < child_count && subbag[i] != nullptr)
                answer += subbag[i]->count(target);
        }
    }
    return answer;
}

template <class Item, std::size_t SomePosNumber>
void bag<Item, SomePosNumber>::show_contents(int indent) const
{
    const int EXTRA_INDENTATION = 4;

    // 리프 노드가 아니면 가장 오른쪽 자식부터 출력
    if (!is_leaf() && child_count > 0)
        subbag[child_count - 1]->show_contents(indent + EXTRA_INDENTATION);

    // 데이터를 역순으로 출력 (큰 값부터)
    for (size_t i = data_count; i > 0; i--) 
    {
        if (indent > 0)
            cout << setw(indent) << " ";
        cout << data[i-1] << endl;

        // 해당 데이터 왼쪽의 자식 출력
        if (!is_leaf() && (i-1) < child_count)
            subbag[i-1]->show_contents(indent + EXTRA_INDENTATION);
    }
}

#endif