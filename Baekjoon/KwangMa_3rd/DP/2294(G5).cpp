#include <iostream>
#include <algorithm>
using namespace std;

int arr[101];
int dp[10001];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= k; i++)
        dp[i] = 10001;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        for (int j = arr[i]; j <= k; j++)
            dp[j] = min(dp[j], dp[j - arr[i]] + 1);
    }
    if(dp[k] == 10001)
        cout << -1 << '\n';
    else
        cout << dp[k] << '\n';
}