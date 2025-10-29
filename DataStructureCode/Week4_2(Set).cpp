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
    bool contains(int value);
    void erase(int value);
    bool is_disjoint(Set &other) const;
    iterator begin();
    iterator end();
    const_iterator find(const int& val);
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

bool Set::contains(int value) {
    return find(value) != end();
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
bool Set::is_disjoint(Set& other) const {
    for (int item : this->data) {
        if (other.contains(item)) {
            return false;
        }
    }
    return true;
}

Set::const_iterator Set::find(const int& val) {
    auto it = lower_bound(data.begin(), data.end(), val);
    if (it != data.end() && *it == val) {
        return it;
    }
    return data.end();
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
    Set yourSet = {3, 12, 8, 9, 7};
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
    std::cout << "\n";
    std::cout << "your set is ";
    for (auto elem : yourSet) {
        std::cout << elem << " ";
    }
    if(mySet.is_disjoint(yourSet))
        std::cout << "\n"
                  << "True";
    else
        std::cout << "\n"
                  << "False";

    std::cout << std::endl;

    return 0;
}
