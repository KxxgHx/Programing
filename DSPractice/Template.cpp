#include <iostream>
using namespace std;

template <typename T>
T Max(T a, T b){
    return (a > b) ? a : b;
}

int main(){
    int a, b;
    double x, y;
    cout << "write two integer num : ";
    cin >> a >> b;
    cout << "write two double num : ";
    cin >> x >> y;
    cout << "Max of integer : " << Max(a, b) << endl;
    cout << "Max of double : " << Max(x, y);
}