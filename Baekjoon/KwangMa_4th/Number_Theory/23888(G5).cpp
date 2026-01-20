#include <iostream>

typedef long long ll;

ll gcd(ll a, ll b) {
    while (b != 0)
    {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll a, d;
    cin >> a >> d;

    int q;
    cin >> q;

    while (q--) {
        ll type, l, r;
        cin >> type >> l >> r;
        
        ll left = a + (l - 1) * d;

        if (type == 1)
        {
            ll right = a + (r - 1) * d;
            ll count = r - l + 1;
            ll sum = (left + right) * count / 2;
            cout << sum << "\n";
        } 
        else {
            if (l == r)
                cout << left << "\n";
             else 
                cout << gcd(left, d) << "\n";
        }
    }

}