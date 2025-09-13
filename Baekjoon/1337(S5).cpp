#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int ans;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int N;
	cin >> N;
	vector<int> vec;
	for (int i = 0; i < N; i++)
	{
		int a;
		cin >> a;
		vec.push_back(a);
	}
	sort(vec.begin(), vec.end());
	ans = 4;
	for (int i = 0; i < N; i++)
	{
		int count = 0;
		for (int j = i; j < N && vec[j] <= vec[i] + 4; j++)
		{
			count++;
		}
		ans = min(ans, 5 - count);
	}
	cout << ans;

}