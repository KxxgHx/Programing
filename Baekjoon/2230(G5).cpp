#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int N, M;
	cin >> N >> M;
	vector<int> A(N);
	int left = 0;
	int right = 0;
	int minimum = 2000000000;
	for (int i = 0; i < N; i++)
	{
		cin >> A[i];
	}
	sort(A.begin(), A.end());

	while (left <= right && right < N)
	{
		int result = A[right] - A[left];
		if (result < M)
		{
			right++;
		}
		else
		{
			minimum = min(result, minimum);
			left++;
		}
	
	}
	cout << minimum;

}