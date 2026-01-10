#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, K;
    cin >> N >> K;

    vector<int> W(N + 1, 0);
    vector<int> V(N + 1, 0);

    for (int i = 1; i <= N; i++)
        cin >> W[i] >> V[i];

    vector<vector<int>> dp(N + 1, vector<int>(K + 1, 0));

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= K; j++)
        {
            if (j < W[i])
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = max(dp[i - 1][j], V[i] + dp[i - 1][j - W[i]]);
        }
    }

    cout << dp[N][K];
}