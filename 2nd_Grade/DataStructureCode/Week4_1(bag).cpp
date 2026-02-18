#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

class Bag {
public:
    static const size_t CAPACITY = 20;
    Bag() : used(0), data() { }

    void insert(const int& entry);
    bool erase_one(const int& target);
    size_t size() const;

    int operator[](size_t i) const;
    void operator+=(const Bag& addend);
    size_t count(const int &target) const;
    void mode(int& value, int& frequency) const;  // 최빈값과 빈도수를 구하는 함수

private:
    int data[CAPACITY];
    size_t used;
};

inline void Bag::insert(const int& entry) {
    assert(size() < CAPACITY);
    data[used++] = entry;
}

inline bool Bag::erase_one(const int& target) {
    int index = 0;
    while ((index < used) && (data[index] != target))
        ++index;
    if (index == used)
        return false;
    --used;
    data[index] = data[used];
    return true;
}

size_t Bag::size() const {
    return used;
}

int Bag::operator[](size_t i) const {
    return data[i];
}

void Bag::operator+=(const Bag& addend) {
    assert(size() + addend.size() <= CAPACITY);
    copy(addend.data, addend.data + addend.used, data + used);
    used += addend.used;
}

size_t Bag::count(const int &target) const{
    int index = 0;
    int cnt = 0;
    while(index < used)
    {
        if(data[index] == target)
        {
            cnt++;
        }
        index++;
    }
    
    return cnt;
}

void Bag::mode(int& value, int& frequency) const {
    if (used == 0) {
        value = -1;
        frequency = 0;
        return;
    }
    
    int maxCount = 0;
    int modeValue = data[0];
    bool visited[CAPACITY] = {false};
    
    for (size_t i = 0; i < used; i++) {
        if (visited[i]) continue;
        
        int currentValue = data[i];
        int currentCount = count(currentValue);
        
        // 같은 값을 다시 세지 않도록 방문 표시
        for (size_t j = i; j < used; j++) {
            if (data[j] == currentValue) {
                visited[j] = true;
            }
        }
        
        if (currentCount > maxCount) {
            maxCount = currentCount;
            modeValue = currentValue;
        }
    }
    
    value = modeValue;
    frequency = maxCount;
}

int main() {
    Bag bag1;
    bag1.insert(1);
    bag1.insert(2);
    bag1.insert(1);
    int n;
    cout << "bag1: ";
    for (size_t i = 0; i < bag1.size(); i++) {
        cout << bag1[i] << " ";
    }
    cout << endl
         << "찾고자 하는 숫자의 갯수 : ";
    cin >> n;
    cout << n << "의 갯수 : " << bag1.count(n);
    cout << endl;
    
    int modeVal, modeFreq;
    bag1.mode(modeVal, modeFreq);
    cout << "bag1의 최빈값: " << modeVal << " (개수: " << modeFreq << ")" << endl << endl;

    Bag bag2;
    bag2.insert(4);
    bag2.insert(1);
    bag2.insert(6);
    bag2.insert(6);

    cout << "bag2: ";
    for (size_t i = 0; i < bag2.size(); i++) {
        cout << bag2[i] << " ";
    }
    cout << endl;
    
    bag2.mode(modeVal, modeFreq);
    cout << "bag2의 최빈값: " << modeVal << " (개수: " << modeFreq << ")" << endl << endl;

    bag2 += bag1;

    cout << "bag2: ";
    for (size_t i = 0; i < bag2.size(); i++) {
        cout << bag2[i] << " ";
    }
    cout << endl
         << "찾고자 하는 숫자의 갯수 : ";
    cin >> n;
    cout << n << "의 갯수 : " << bag2.count(n);
    cout << endl;
    
    bag2.mode(modeVal, modeFreq);
    cout << "bag2의 최빈값: " << modeVal << " (개수: " << modeFreq << ")" << endl;

    return 0;
}