#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> pp;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;

    vector<pp> items; 

    for (int i = 0; i < N; i++)
    {
        int V, C, K;
        cin >> V >> C >> K;

        int bit = 1;
        while (K > 0)
        {
            int num = min(K, bit);
            items.push_back({V * num, C * num}); 
            
            K -= num;
            bit *= 2;
        }
    }

    vector<int> dp(M + 1, 0);

    for (int i = 0; i < items.size(); i++)
    {
        int weight = items[i].first;
        int value = items[i].second;

        for (int j = M; j >= weight; j--)
        {
            dp[j] = max(dp[j], dp[j - weight] + value);
        }
    }

    cout << dp[M];
}