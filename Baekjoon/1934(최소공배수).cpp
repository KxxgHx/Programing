#include <iostream>

using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}
int lcm(int a, int b) {
    return (a / gcd(a, b)) * b; 
}

int main() {
    int testCase;
    cin >> testCase; 

    while (testCase--) {
        int A, B;
        cin >> A >> B;
        cout << lcm(A, B) << endl;
    }

    return 0;
}
