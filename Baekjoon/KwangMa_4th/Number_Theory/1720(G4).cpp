#include <iostream>

using namespace std;

int N;
int dp[31];

int main()
{
    cin >> N;

    dp[0] = dp[1] = 1;

    for (int i = 2; i <= N; i++)
        dp[i] = dp[i - 1] + dp[i - 2] * 2;

    if (N % 2)
        cout << (dp[N] + dp[N / 2]) / 2 << "\n";
    else
        cout << (dp[N] + dp[N / 2] + 2 * dp[N / 2 - 1]) / 2 << "\n";
}