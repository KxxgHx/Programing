#include <iostream>
using namespace std;

int dp[1001][1001];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int N, K;

    // C(n,k) = C(n-1,k-1) + C(n-1,k)
    for (int i = 0; i <= 1000; i++) {
        dp[i][0] = 1;
        dp[i][i] = 1;
        
        for (int j = 1; j < i; j++) {
            dp[i][j] = (dp[i-1][j-1] + dp[i-1][j]) % 10007;
        }
    }
    
    cin >> N >> K;
    cout << dp[N][K] << '\n';
    
    return 0;
}