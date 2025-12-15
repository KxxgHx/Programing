//umap으로 성공
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
		if (sum[i] == K) //구간 자체가 K인 경우
			cnt++;
		if (aa.find(sum[i] - K) != aa.end()) // sum[i]-K가 이전에 구간합으로 있을 때
		{
			cnt += aa[sum[i] - K]; //여러 개 일수도 있으니 aa[sum[i]-K]만큼 더하기
		}
		aa[sum[i]]++; //뒤에서도 쓰게해야댐
	}
	
	cout << cnt;
}
