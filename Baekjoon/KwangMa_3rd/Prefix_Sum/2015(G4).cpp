#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int N;
	ll K;
	ll cnt = 0;
	cin >> N >> K;
	vector<ll> vec(N + 1);
	vector<ll> sum(N + 1);
	vec[0] = 0;
	sum[0] = 0;
	unordered_map<ll, ll> aa;

	for (int i = 1; i <= N; i++)
	{
		cin >> vec[i];
		sum[i] = vec[i] + sum[i - 1];
	}
	for (int i = 1; i <= N; i++)
	{
		if (sum[i] == K)
			cnt++;
		if (aa.find(sum[i] - K) != aa.end())
		{
			cnt += aa[sum[i] - K];
		}
		aa[sum[i]]++;
	}
	
	cout << cnt;
}