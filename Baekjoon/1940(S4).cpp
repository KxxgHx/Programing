#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int N;
	int M;
	cin >> N;
	cin >> M;
	vector<int> v;
	int left = 0;
	int right = N - 1;
	int result = 0;
	for (int i = 0; i < N; i++)
	{
		int insert;
		cin >> insert;
		v.push_back(insert);
	}
	sort(v.begin(), v.end());
	while (left < right)
	{
		if (v[left] + v[right] == M)
		{
			left++;
			right--;
			result++;
		}
		else if (v[left] + v[right] > M)
		{
			right--;
		}
		else
			left++;
	}
	cout << result << '\n';
}