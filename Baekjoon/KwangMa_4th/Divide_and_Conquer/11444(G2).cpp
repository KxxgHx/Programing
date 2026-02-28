#include <iostream>
#include <map>

using namespace std;
typedef long long ll;
#define MOD 1000000007

map<ll, ll> fib;

ll fibo(ll n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    if (n == 2)
        return 1;

    if (fib.count(n) > 0)
        return fib[n];

    if (n % 2 == 0)
    {
        ll m = n / 2;
        ll f = fibo(m - 1);
        ll next_f = fibo(m);
        ll two = 2;
        fib[n] = ((two * f + next_f) * next_f) % MOD;
        return fib[n];
    }
    ll m = (n + 1) / 2;
    ll next_f = fibo(m);
    ll f = fibo(m - 1);
    fib[n] = (f * f + next_f * next_f) % MOD;
    return fib[n];
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll N;
    cin >> N;
    cout << fibo(N);

    return 0;
}