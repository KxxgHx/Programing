#include <iostream>

using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int left = 1;
	int right = 1;
	int N;
	int sum = 0;
	int sol = 0;
	cin >> N;
	while (left <= right && right <= N + 1)
	{
		if (sum > N)
		{
			sum -= left;
			left++;
		}
		else if (sum == N)
		{
			sol++;
			sum += right;
			right++;
		}
		else
		{
			sum += right;
			right++;
		}
	}
	cout << sol;
}