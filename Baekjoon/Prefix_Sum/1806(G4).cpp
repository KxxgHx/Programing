#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int N, S;
	int a;
	cin >> N >> S;
	vector<int> arr;
	for (int i = 0; i < N; i++)
	{
		cin >> a;
		arr.push_back(a);
	}
	int left = 0;
	int right = 0;
	int min_len = N + 1;
	int sum = 0;
	a = 0;
	while (right < N)
	{
		sum += arr[right++];
		while (sum >= S)
		{
			min_len = min(min_len, right - left);
			sum -= arr[left++];
		}
	}
	if (min_len == N + 1)
	{
		cout << 0 << "\n";
	}	
	else
		cout << min_len;
}