#include <iostream>
#include "Array.h"
using namespace std;

int main() {
    Array<int, 5> a1 = {1, 2, 3};
    Array<double, 4> a2 = {1.1, 2.2};
    Array<string, 3> a3 = {"apple", "banana"};

    cout << "int 배열: ";
    for (auto x : a1) cout << x << " ";
    cout << "\n";

    cout << "double 배열: ";
    for (auto x : a2) cout << x << " ";
    cout << "\n";

    cout << "string 배열: ";
    for (auto& s : a3) cout << s << " ";
    cout << "\n";

    // 수정 테스트
    a3[2] = "cherry";
    cout << "수정 후 string 배열: ";
    for (auto& s : a3) cout << s << " ";
    cout << "\n";

    return 0;
}
