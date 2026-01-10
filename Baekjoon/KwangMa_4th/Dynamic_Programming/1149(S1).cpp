#include <iostream>
#include <algorithm>

using namespace std;

int dp[1001][3];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    int RGB[3];
    dp[0][0] = 0;
    dp[0][1] = 0;
    dp[0][2] = 0;

    cin >> N;

    for (int i = 1; i <= N; i++)
    {
        cin >> RGB[0] >> RGB[1] >> RGB[2];
        dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + RGB[0];
        dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + RGB[1];
        dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]) + RGB[2];
    }

    cout << min(dp[N][2], min(dp[N][0], dp[N][1]));
}