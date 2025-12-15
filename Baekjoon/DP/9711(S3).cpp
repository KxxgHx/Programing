#include <iostream>
using namespace std;

long long fibo[10001];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int T, P, Q;
	cin >> T;
	
	for (int i = 1; i <= T; i++)
	{
		fibo[1] = 1;
		fibo[2] = 1;
		cin >> P >> Q;
		for (int j = 3; j <= P; j++)
		{
			fibo[j] = (fibo[j - 1] + fibo[j - 2]) % Q;
		}
		cout << "Case #" << i << ": " << fibo[P]%Q << "\n";
	}
}