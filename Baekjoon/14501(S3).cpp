#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;
    vector<int> Ti(N + 1);
    vector<int> Pi(N + 1);

    for (int i = 1; i <= N; i++)
    {
        cin >> Ti[i] >> Pi[i];
    }
    vector<int> dp(N + 2, 0);
    int next = 0;
    for (int i = N; i >= 1; --i)
    {
        next = i + Ti[i]; // 상담을 끝내고 다음으로 가는 날짜
        if (next <= N + 1)
        {
            dp[i] = max(Pi[i] + dp[next], dp[i + 1]); //오늘 상담하는 경우와 상담하지 않는 경우를 비교하여 넣기
        }
        else
            dp[i] = dp[i + 1]; //N을 초과 시 상담 불가 => 다음 날의 최대 수입 가져오기
    }

    cout << dp[1];
}