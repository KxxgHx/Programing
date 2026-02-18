#include <iostream>
#include <iterator>
#include <initializer_list>
#include <stdexcept>
using namespace std;

template<typename T, size_t SIZE>
class Array {
private:
    T data[SIZE];
    using iterator = T*;
public:
    Array();
    Array(initializer_list<T> init);

    T& operator[](size_t index);
    size_t size() const;

    iterator begin();
    iterator end();
};

// 기본 생성자
template<typename T, size_t SIZE>
Array<T, SIZE>::Array() {
    for (size_t i = 0; i < SIZE; ++i)
        data[i] = T(); // 타입별 기본값 초기화
}

// initializer_list 생성자
template<typename T, size_t SIZE>
Array<T, SIZE>::Array(initializer_list<T> init) {
    if (init.size() > SIZE)
        throw out_of_range("Initializer list exceeds array size");

    size_t i = 0;
    for (const auto& elem : init)
        data[i++] = elem;

    for (; i < SIZE; ++i)
        data[i] = T();
}

template<typename T, size_t SIZE>
T& Array<T, SIZE>::operator[](size_t index) {
    if (index >= SIZE)
        throw out_of_range("Index out of range");
    return data[index];
}

template<typename T, size_t SIZE>
size_t Array<T, SIZE>::size() const {
    return SIZE;
}

template<typename T, size_t SIZE>
typename Array<T, SIZE>::iterator Array<T, SIZE>::begin() {
    return data;
}

template<typename T, size_t SIZE>
typename Array<T, SIZE>::iterator Array<T, SIZE>::end() {
    return data + SIZE;
}
