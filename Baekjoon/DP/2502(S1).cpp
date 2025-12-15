#include <iostream>

using namespace std;

int D, K;
int a[31], b[31];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> D >> K;
	a[1] = 1;	a[2] = 0; //a는 첫 번째 날에 1개, 두 번째 날에 0개
	b[1] = 0;	b[2] = 1; //b는 첫 번째 날에 0개, 두 번째 날에 1개

	for (int i = 3; i <= D; i++) {
		a[i] = a[i - 1] + a[i - 2];
		b[i] = b[i - 1] + b[i - 2];
	}
	
	for (int i = 1; i <= K; i++)
	{
		int aa = K - (a[D] * i);
		if (aa % b[D] == 0)
		{
			cout << i << "\n" << aa / b[D] << "\n";
			return 0;
		}
	}
}