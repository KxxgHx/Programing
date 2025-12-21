#include <iostream>
using namespace std;

int dp[1025][1025];
int arr[1025][1025];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int N, M;
	int result = 0;
	cin >> N >> M;
	dp[0][0] = 0;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			cin >> arr[i][j];
			dp[i][j] = arr[i][j] + dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
		}
	}
	int K, x1, y1, x2, y2;
	cin >> K;
	while (K > 0)
	{
		cin >> x1 >> y1 >> x2 >> y2;
		result = dp[x2][y2] - dp[x1 - 1][y2] - dp[x2][y1 - 1] + dp[x1 - 1][y1 - 1];
		cout << result << '\n';
		K--;

	}
}
