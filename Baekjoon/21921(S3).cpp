#include <iostream>
using namespace std;
typedef long long ll;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int N, X;
    cin >> N >> X;
    ll prefix_sum[250001];
    for (int i = 1; i <= N;i++)
    {
        ll a;
        cin >> a;
        prefix_sum[i] = prefix_sum[i - 1] + a;
    }
    ll maxS = prefix_sum[X - 1];
    int cnt = 1;
    for (int i = X; i <= N; i++)
    {
        if(maxS<prefix_sum[i] - prefix_sum[i-X])
        {
            maxS = prefix_sum[i] - prefix_sum[i - X];
            cnt = 1;
        }
        else if(maxS == prefix_sum[i] - prefix_sum[i-X])
            cnt += 1;
    }
    if(maxS == 0)
        cout << "SAD";
    else
        cout << maxS << '\n'
             << cnt;
}