#include <iostream>

using namespace std;

int coin[10];

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N, K;
	int result = 0;
	cin >> N >> K;

	for (int i = 0; i < N; i++)
	{
		cin >> coin[i];
	}
	for (int i = N - 1; i >= 0; i--)
	{
		if (K >= coin[i])
		{
			result += K / coin[i];
			K %= coin[i];
		}
	}
	cout << result;
}
