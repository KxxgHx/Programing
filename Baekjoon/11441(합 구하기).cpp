#include <iostream>
using namespace std;
int arr[100001];
int sum[100001];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int N;
	cin >> N;
	arr[0] = 0;
	sum[0] = 0;

	for (int i = 1; i <= N; i++)
	{
		cin >> arr[i];
		sum[i] = sum[i - 1] + arr[i];
	}
	int M, x, y, result;
	cin >> M;
	for (int i = 1; i <= M; i++)
	{
		cin >> x >> y;
		result = sum[y] - sum[x - 1]; //x가 아닌 x-1인 이유는 범위가 x~y까지이기 때문에 주의 해야함(이거때문에 5분 날림)
		cout << result << '\n';
	}
}
