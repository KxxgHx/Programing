#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int minToOne(int n) {
    vector<int> dp(n + 1, 0);

    for (int i = 2; i <= n; i++) {
        // 기본 연산: 1을 빼는 경우
        dp[i] = dp[i - 1] + 1;

        // 2로 나누어 떨어지는 경우
        if (i % 2 == 0)
            dp[i] = min(dp[i], dp[i / 2] + 1);

        // 3으로 나누어 떨어지는 경우
        if (i % 3 == 0)
            dp[i] = min(dp[i], dp[i / 3] + 1);
    }

    return dp[n];
}

int main() {
    int n;
    cin >> n;
    cout << minToOne(n) << endl;
    return 0;
}
