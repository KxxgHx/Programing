#include <iostream>
#include <vector>
using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int N;
	cin >> N;
	vector<long long> num(N), sum(N + 1);
	long long result = 0;
	sum[0] = 0;
	for (int i = 0; i < N; i++)
	{
		cin >> num[i];
		sum[i + 1] = sum[i] + num[i];
	}

	for (int i = 0; i < N - 1; i++)
	{
		result += num[i] * (sum[N] - sum[i + 1]);
	}

	cout << result;

}
