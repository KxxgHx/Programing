#include <iostream>
using namespace std;

typedef long long ll;


int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	ll dp[1001] = { 0 };
	ll count = 0;
	int N, M;
	ll num;
	ll sum = 0;
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		cin >> num;
		sum += num;	
		dp[sum % M]++;
		if (sum % M == 0)
			count++;
	}

	for (int i = 0; i <= M; i++)
	{
		if(dp[i] != 0)
			count += dp[i] * (dp[i] - 1) / 2;
	}

	cout << count;

}
