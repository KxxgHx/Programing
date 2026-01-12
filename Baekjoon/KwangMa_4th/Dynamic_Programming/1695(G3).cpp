#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    vector<int> vec(N);
    for (int i = 0; i < N; i++) {
        cin >> vec[i];
    }

    vector<int> rev_vec = vec;
    reverse(rev_vec.begin(), rev_vec.end());

    
    vector<int> dp(N + 1, 0);
    vector<int> before(N + 1, 0);

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (vec[i - 1] == rev_vec[j - 1]) {
                dp[j] = before[j - 1] + 1;
            } else {
                dp[j] = max(before[j], dp[j - 1]);
            }
        }
        before = dp;
    }
    cout << N - dp[N] << endl;

    return 0;
}