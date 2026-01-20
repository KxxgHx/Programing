#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;

ll D[51];
ll M[51];

ll Mgcd, Dlcm;

ll gcd(ll a, ll b) {
    while (b != 0) {
        ll temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

ll lcm(ll a, ll b)
{
    return (a / gcd(a, b)) * b;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int D_size, M_size;
    int cnt = 0;
    cin >> D_size >> M_size;

    for (int i = 0; i < D_size; i++)
        cin >> D[i];
    for (int i = 0; i < M_size; i++)
        cin >> M[i];

    Mgcd = M[0];
    for (int i = 1; i < M_size; i++)
        Mgcd = gcd(Mgcd, M[i]);

    Dlcm = 1;
    for (int i = 0; i < D_size; i++)
    {
        Dlcm = lcm(Dlcm, D[i]);
        if (Dlcm == 0 || Dlcm > Mgcd)
        {
            cout << 0;
            return 0;
        }
    }

    for (ll i = 1; i * i <= Mgcd; i++)
    {
        if (Mgcd % i == 0)
        {
            if (i % Dlcm == 0)
                cnt++;
            if (i * i != Mgcd && ((Mgcd / i) % Dlcm == 0))
                cnt++;
        }
        
    }

    cout << cnt;
}