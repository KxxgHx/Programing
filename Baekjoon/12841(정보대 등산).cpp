#include <iostream>
using namespace std;

typedef long long ll;

ll xleft[100001];
ll xright[100001];
ll cross[100001];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	xleft[0] = 0;
	xright[0] = 0;
	int n;
	long long min = 10000000000;
	cin >> n;
	int Fcross = 0;

	for (int i = 0; i < n; i++)
	{
		cin >> cross[i];
	}
	for (int i = 1; i < n; i++)
	{
		cin >> xleft[i];
		xleft[i] += xleft[i - 1];
	}
	for (int i = 1; i < n; i++)
	{
		cin >> xright[i];
		xright[i] += xright[i - 1];
	}
	for (int i = 0; i < n; i++)
	{
		long long length = xleft[i] + cross[i] + xright[n - 1] - xright[i];
		if (length < min)
		{
			min = length;
			Fcross = i + 1;
		}
	}

	cout << Fcross << " " << min;

}
