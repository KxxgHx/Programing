#include <iostream>
#include <algorithm>

using namespace std;

int A[1001];
int dp[1001];

int main()
{
    int N;
    cin >> N;
    
    int result = 0;

    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        
        dp[i] = 1; 

        for (int j = 0; j < i; j++)
        {
            if (A[j] < A[i])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        
        if (result < dp[i])
            result = dp[i];
    }

    cout << result;
}