#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Set {
private:
    using iterator = typename std::vector<int>::iterator;
    using const_iterator = typename std::vector<int>::const_iterator;
    std::vector<int> data;
    

public:
    Set();
    Set(std::initializer_list<int> init);

    void insert(int value);
    bool contains(int value) const;
    void erase(int value);
    bool is_disjoint(const Set &other) const;
    iterator begin();
    iterator end();
    const_iterator find(const int& val) const;
    const_iterator lower_bound_const(const_iterator first, const_iterator last, const int& value) const;
    iterator lower_bound(iterator first, iterator last, const int& value) const;
};

Set::Set() {}

Set::Set(std::initializer_list<int> init) {
    for (const auto& elem : init) {
        insert(elem);
    }
}

void Set::insert(int value) {
    if (!contains(value)) {
        data.push_back(value);
        std::sort(data.begin(), data.end());
    }
}

bool Set::contains(int value) const {
    return find(value) != data.end();
}

void Set::erase(int value) {
    auto it = std::find(data.begin(), data.end(), value);
    if (it != data.end()) {
        data.erase(it);
    }
}

Set::iterator Set::begin() {
    return data.begin();
}

Set::iterator Set::end() {
    return data.end();
}

Set::const_iterator Set::find(const int& val) const {
    auto it = lower_bound_const(data.begin(), data.end(), val);
    if (it != data.end() && *it == val) {
        return it;
    }
    return data.end();
}

bool Set::is_disjoint(const Set &other) const
{
    for (const auto& elem : data) {
        if (other.contains(elem)) {
            return false;
        }
    }
    return true;
}

typename Set::const_iterator Set::lower_bound_const(const_iterator first, const_iterator last, const int& value) const {
    while (first < last) {
        const_iterator mid = first + (last - first) / 2;
        if (*mid < value) {
            first = mid + 1;
        } else {
            last = mid;
        }
    }
    return first;
}

typename Set::iterator Set::lower_bound(iterator first, iterator last, const int& value) const {
    while (first < last) {
        iterator mid = first + (last - first) / 2;
        if (*mid < value) {
            first = mid + 1;
        } else {
            last = mid;
        }
    }
    return first;
}

int main() {
    Set mySet = { 1, 2, 3, 4, 5 };

    std::cout << "My set is ";
    for (auto elem : mySet) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    mySet.insert(6);
    mySet.erase(3);

    if (mySet.find(4) != mySet.end()) {
        std::cout << "4 is in the set." << std::endl;
    }

    std::cout << "My set is ";
    for (auto elem : mySet) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // is_disjoint 테스트
    Set set1 = {1, 2, 3};
    Set set2 = {4, 5, 6};
    Set set3 = {3, 4, 5};
    
    std::cout << "set1 and set2 are disjoint: " << set1.is_disjoint(set2) << std::endl;
    std::cout << "set1 and set3 are disjoint: " << set1.is_disjoint(set3) << std::endl;

    return 0;
}