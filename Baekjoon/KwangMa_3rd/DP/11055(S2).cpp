#include <iostream>
#include <algorithm>

using namespace std;

int A[1001];
int dp[1001];
int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        dp[i] = A[i];
        for (int j = 0; j < i; j++)
        {
            if (A[j] < A[i])
                dp[i] = max(dp[i], A[i] + dp[j]);
        }
    }
    int result = 0;
    for (int i = 0; i < N; i++)
    {
        if(result<dp[i])
            result = dp[i];
    }
    cout << result;
}