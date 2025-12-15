#include <iostream>
#include <algorithm>
#include <string>

using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
    if (b > a) {
        swap(a, b);
    }
    
    while (b != 0) {
        ll temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    ll A, B; 
    cin >> A >> B;
    
    ll num = gcd(A, B); 
    
    for (ll i = 0; i < num; i++) {
        cout << '1'; 
    }
    
    return 0;
}