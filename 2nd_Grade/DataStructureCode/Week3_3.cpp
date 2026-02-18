#include <iostream>
#include <array>
#include <string>
using namespace std;

array<int, 26> arr1;
array<int, 26> arr2;
int main()
{
    string a, b;
    cin >> a >> b;
    char c;
    int index = 0;
    for (int i = 0; i < a.length(); i++){
        c = a[i];
        index = c - 'a';
        arr1[index]++;
    }
    for (int i = 0; i < b.length(); i++){
        c = b[i];
        index = c - 'a';
        arr2[index]++;
    }
    if(arr1 == arr2)
    {
        cout << "에너그램이다";
    }
    else
        cout << "에너그램이 아니다";
}