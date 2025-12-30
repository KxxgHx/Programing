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

    string str1, str2;
    cin >> str1 >> str2;
    int a = str1.size();
    int b = str2.size();
    vector<vector<int>> dp(a + 1, vector<int>(b + 1, 0));

    for (int i = 1; i <= a; i++)
    {
        for (int j = 1; j <= b; j++)
        {
            if (str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }

    }
    cout << dp[a][b] << '\n';

    if (dp[a][b] > 0)
    {
        string result = "";
        int i = a;
        int j = b;

        while (i > 0 && j > 0)
        {
            if (dp[i][j] == dp[i - 1][j - 1] + 1 &&str1[i - 1] == str2[j - 1])
            {
                result += str1[i - 1];
                i--;
                j--;
            }
            else
            {
                if (dp[i][j] == dp[i - 1][j])
                    i--;
                else
                    j--;
            }
        }
        reverse(result.begin(), result.end());
        cout << result;
    }
}