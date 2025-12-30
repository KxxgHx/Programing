#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str1, str2, str3;
    cin >> str1 >> str2 >> str3;

    int a = str1.size();
    int b = str2.size();
    int c = str3.size();

    vector<vector<vector<int>>> dp(a + 1, vector<vector<int>>(b + 1, vector<int>(c + 1, 0)));

    for (int i = 1; i <= a; i++)
    {
        for (int j = 1; j <= b; j++)
        {
            for (int k = 1; k <= c; k++)
            {
                if (str1[i - 1] == str2[j - 1] && str2[j - 1] == str3[k - 1])
                {
                    dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
                }
                else
                {
                    dp[i][j][k] = max({dp[i - 1][j][k], dp[i][j - 1][k], dp[i][j][k - 1]});
                }
            }
        }
    }

    cout << dp[a][b][c] << '\n';
    
    return 0;
}