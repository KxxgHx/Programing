#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll MAX = 10000001; 
bool isPrime[MAX]; 


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll A, B;
    cin >> A >> B;

    fill(isPrime, isPrime + MAX, true);
    isPrime[0] = isPrime[1] = false;

    for (ll i = 2; i * i < MAX; i++) {
        if (isPrime[i]) {
            for (ll j = i * i; j < MAX; j += i)
                isPrime[j] = false;
        }
    }

    ll cnt = 0;

    for (ll i = 2; i < MAX; i++) {
        if (isPrime[i]) {
            ll lilnum = i;
            
            while (lilnum <= B / i) {
                lilnum *= i;
                if (lilnum >= A)
                {
                    cnt++;
                }
            }
        }
    }

    cout << cnt;
    return 0;
}