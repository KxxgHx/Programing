#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;

bool isSquare[10000001];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll Min, Max;
    cin >> Min >> Max;

    ll cnt = Max - Min + 1;

    ll result = 0;

    for (ll i = 2; i * i <= Max; i++)
    {
        ll n = Min / (i * i);

        if (Min % (i * i) != 0)
            n++;
        while (n * (i * i) <= Max)
        {
            isSquare[n * (i * i) - Min] = true;
            n++;
        }
    }

    for (ll i = 0; i < cnt; i++)
    {
        if(isSquare[i] == false)
            result++;
    }

    cout << result;
}