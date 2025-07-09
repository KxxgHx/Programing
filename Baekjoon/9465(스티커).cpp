#include <iostream>

using namespace std;

long long input[2][100001];
long long dp[2][100001];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int T;
	int n;

	cin >> T;
	for (int a = 0; a < T; a++)
	{
		cin >> n;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 1; j < n + 1; j++)
			{
				cin >> input[i][j];
			}
		}
		dp[0][0] = 0;
		dp[1][0] = 0;
		dp[0][1] = input[0][1];
		dp[1][1] = input[1][1];

		for (int k = 2; k < n + 1; k++)
		{
			dp[0][k] = max(dp[1][k - 1], dp[1][k - 2]) + input[0][k]; //자기자신 + 이전 대각선 또는 이전이전 대각선을 이용하는 방법밖에 없음
			dp[1][k] = max(dp[0][k - 1], dp[0][k - 2]) + input[1][k];
		}
		cout << max(dp[0][n], dp[1][n])<<endl; //두 case에서도 더 큰 놈 골라서 출력
	}

	
}
