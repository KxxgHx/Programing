#include <iostream>
using namespace std;
int dp[50001];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	
	cin >> n;
	for (int i = 1; i < 224; i++) //224인 이유는 제곱 시 50000보다 적은 수 중 가장 가까운게 223
	{
		dp[i * i] = 1;
	}

	for (int i = 1; i <= n; i++)
	{
		if (dp[i] != 1)
		{
			int minimum = 30000;
			for (int j = 1; j*j <= i; j++)
			{
				int a = dp[j * j] + dp[i - (j * j)];
				if (minimum > a)
				{
					minimum = a;
					
				}
				
			}
			dp[i] = minimum;
		}
	}

	cout << dp[n];


}