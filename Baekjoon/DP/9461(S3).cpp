#include <iostream>
long long dp[101];
using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N;
	int T;

	dp[0] = 0;
	dp[1] = 1;
	dp[2] = 1;
	dp[3] = 1;

	for (int i = 4; i < 101; i++)
	{
		dp[i] = dp[i - 2] + dp[i - 3];
	}
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> N;
		cout << dp[N] << '\n';
	}
	
}