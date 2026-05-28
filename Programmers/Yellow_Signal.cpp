#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;

ll gcd(ll a, ll b)
{
    if(b == 0)
        return a;
    else
        return gcd(b, a % b);
}

ll lcm(ll a, ll b)
{
    return a / gcd(a, b) * b;
}

ll solution(vector<vector<int>> signals) {
    ll tot_Lcm = 1;

    for (auto &sig : signals)
    {
        int time = sig[0] + sig[1] + sig[2];
        tot_Lcm = lcm(tot_Lcm, time);
    }

    vector<int> result(tot_Lcm + 1, 1);
    result[0] = 0;

    for(auto &sig : signals)
    {
        int g = sig[0];
        int y = sig[1];
        int time = g + y + sig[2];

        vector<int> yellow(tot_Lcm + 1, 0);
        for (ll t = g + 1; t <= tot_Lcm; t+= time)
        {
            for (int i = 0; i < y && t + i <= tot_Lcm; i++)
            {
                yellow[t + i] = 1;
            }
        }
        for (ll i = 1; i <= tot_Lcm; i++)
            result[i] = result[i] && yellow[i];
    }
    for (ll i = 1; i <= tot_Lcm; i++)
    {
        if(result[i])
            return i;
    }
    return -1;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<vector<int>> signals(n, vector<int>(3));
    for (int i = 0; i < n; i++)
    {
        cin >> signals[i][0] >> signals[i][1] >> signals[i][2];
    }

    cout << solution(signals) << "\n";
}